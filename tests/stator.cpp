// This code simulates the static magnetic field created by 5 permanent magnets (1cm x 1cm) placed side by side.
// A steel region above the magnets is perturbing the magnetic field lines.
//
// The magnetic scalar potential is used to solve this problem. This is valid since there are no current sources.
// The permanent magnets are treated as pre-magnetised pieces of non-magnetic material (since all magnetic domains are already fully oriented).


#include "sparselizardbase.h"


using namespace mathop;

void sparselizard(void)
{

    int coil_1 = 1, coil_2 = 2, core=3, air = 4, skin_coil_1 = 5, skin_coil_2 = 6, skin_core = 7, pm_1=8, pm_2 = 2, pm_holder = 10,
        in_1 = 11, in_2 = 12, out_1 = 13, out_2 = 14, domainboundary = 15, zeropotential = 16;

    // The domain regions as defined in 'halbacharray.geo':
    //int magnet1 = 1, magnet2 = 2, magnet3 = 3, magnet4 = 4, magnet5 = 5, steel = 6, air = 7, zeropotential = 8;

    // The mesh can be curved!
    mesh mymesh("../../models/stator.msh");

    // Define new physical regions for convenience:
    int magnets = regionunion({pm_1, pm_2});

    // Define extra regions for convenience:
    int conductor = regionunion({coil_1,coil_2,core});

    int wholedomain = regionunion({magnets,conductor, air, pm_holder});

    domainboundary = regionunion({domainboundary,in_1,in_2,out_1,out_2});

    parameter mu, sigma;
    // Define the magnetic permeability mu [H/m] everywhere (the materials here are not magnetic):
    mu|wholedomain = 4*getpi()*1e-7;
    // Conductivity of the copper coil and aluminium tube [S/m]:
    sigma|coil_1 = 6e7;
    sigma|coil_2 = 6e7;
    sigma|core = 7.69e6;

    // Set the working frequency to 50 Hz:
    setfundamentalfrequency(50);

    // Define a spanning tree to gauge the magnetic vector potential (otherwise the matrix to invert is singular).
    // Start growing the tree from the regions with constrained potential vector (here the domain boundary):
    spanningtree spantree({domainboundary});

    // Use nodal shape functions 'h1' for the electric scalar potential 'v'.
    // Use edge shape functions 'hcurl' for the magnetic vector potential 'a'.
    // A spanning tree has to be provided to field 'a' for gauging.
    // Since the solution has a component in phase with the electric actuation
    // and a quadrature component we need 2 harmonics at 50Hz
    // (harmonic 1 is DC, 2 is sine at 50Hz and 3 cosine at 50Hz).
    field a("hcurl", {2,3}, spantree), v("h1", {2,3});

    // Gauge the vector potential field on the whole volume:
    a.setgauge(wholedomain);

    // Select adapted interpolation orders for field a and v (default is 1):
    a.setorder(wholedomain, 0);

    // Put a magnetic wall (i.e. set field a to 0) all around the domain (no magnetic flux can cross it):
    a.setconstraint(domainboundary);
    // Also ground v on face 'vout':
    v.setconstraint(out_1);
    v.setconstraint(out_2);
    // Set v to 1V on face 'vin' for the in-phase component and to 0 for the quadrature component:
    v.harmonic(2).setconstraint(in_1, 1);
    v.harmonic(3).setconstraint(in_1);

    // Define the weak magnetodynamic formulation:
    formulation magdyn;

    // The strong form of the magnetodynamic a-v formulation is
    //
    // curl( 1/mu * curl(a) ) + sigma * (dt(a) + grad(v)) = js, with b = curl(a) and e = -dt(a) - grad(v)
    //
    // Magnetic equation:
    magdyn += integral(wholedomain, 1/mu* curl(dof(a)) * curl(tf(a)) );
    magdyn += integral(conductor, sigma*dt(dof(a))*tf(a) + sigma* grad(dof(v))*tf(a) );
    // Electric equation:
    magdyn += integral(conductor, sigma*grad(dof(v))*grad(tf(v)) + sigma*dt(dof(a))*grad(tf(v)) );

    // Generate the algebraic matrices A and vector b of the Ax = b problem:
    magdyn.generate();

    // Get the x solution vector:
    vec sol = solve(magdyn.A(), magdyn.b());

    // Update the fields with the solution that has just been computed:
    a.setdata(wholedomain, sol);
    v.setdata(conductor, sol);

    // Write the magnetic induction field b = curl(a) [T], electric field e = -dt(a) - grad(v) [V/m] and current density j [A/m^2]:
    expression e = -dt(a) - grad(v);

    curl(a).write(wholedomain, "../../results/stator/b.pos");
    e.write(conductor, "../../results/stator/e.pos");
    (sigma*e).write(conductor, "../../results/stator/j.pos");
    v.write(conductor, "../../results/stator/v.pos");

    // magnets

    // Nodal shape functions 'h1' for the magnetic scalar potential 'phi'.
    field phi("h1");

    // Use interpolation order 2 on the whole domain:
    phi.setorder(wholedomain, 2);

    // The magnetic scalar potential (just like the electric potential)
    // needs to be fixed at least at one node to have a well-posed problem.
    // Here it is forced to 0 at a permanent magnet corner point.
    phi.setconstraint(zeropotential);

    // Vacuum magnetic permeability [H/m]:
    double mu0 = 4*getpi()*1e-7;

    mu|air = mu0;
    mu|core = 1000*mu0;
    mu|magnets = mu0;


    formulation magnetostatic;

    // In the absence of current sources the static Maxwell equations give:
    //
    // curl h = 0
    //
    // One can thus define a magnetic scalar potential 'phi' such that h = -grad(phi)
    //
    // Considering also that div(b) = 0 we get
    //
    // div(mur*(-grad(phi))) = 0
    //
    // with b = mur * h.
    //
    // In the permanent magnet region b = mu0 * (h + m),
    // i.e. the material is non-magnetic but it is pre-magnetised by the magnetisation vector m [A/m].
    // We thus get:
    // div(mu0*(-grad(phi)) + mu0*m) = 0
    //
    // For a permanent magnet with a 1 Tesla magnetic induction b in the y direction we have:
    //
    // m = [0, 1 Tesla / mu0] or about [0, 800e3] A/m

    // The weak form corresponding to the above equations:
    magnetostatic += integral(wholedomain, -grad(dof(phi)) * mu * grad(tf(phi)) );

    // This is when all magnets are oriented in the y direction:
    magnetostatic += integral(magnets, array2x1(0, 800e3) * mu * grad(tf(phi)) );
    // This is in Halbach configuration (to maximise the magnetic field above the array):
    //magnetostatic += integral(magnet1, array2x1(-800e3, 0) * mu * grad(tf(phi)) );
    //magnetostatic += integral(magnet2, array2x1(0, -800e3) * mu * grad(tf(phi)) );
    //magnetostatic += integral(magnet3, array2x1(800e3, 0) * mu * grad(tf(phi)) );
    //magnetostatic += integral(magnet4, array2x1(0, 800e3) * mu * grad(tf(phi)) );
    //magnetostatic += integral(magnet5, array2x1(-800e3, 0) * mu * grad(tf(phi)) );


    magnetostatic.generate();

    // Solve the algebraic system Ax = b:
    sol = solve(magnetostatic.A(), magnetostatic.b());

    // Transfer the data from the solution vector to the phi field:
    phi.setdata(wholedomain, sol);

    // Write the magnetic scalar potential and the magnetic field with an order 2 interpolation.
    phi.write(wholedomain, "../../results/stator/phi.pos", 2);
    norm(-grad(phi)).write(wholedomain, "../../results/stator/hnorm.pos", 2);
    (-grad(phi)).write(wholedomain, "../../results/stator/h.pos");

    // Evaluate the magnetic field 1cm above the center of the magnet array:
    std::vector<double> magfieldnorm = norm(-grad(phi)).interpolate(wholedomain, {0,0.02,0});
    std::cout << "Magnetic field 1cm above the array center: " << magfieldnorm[0] << " A/m" << std::endl;

    // Write 20 magnetic field lines starting on the top side of the magnet array:
    shape ln("line", -1, {-0.025,0.01,0, 0.025,0.01,0}, 20);
    (-grad(phi)).streamline(regionexclusion(wholedomain, magnets), "../../results/stator/magneticfieldline.pos", ln.getcoords(), 0.01/5);


    // The MAGNETOSTATIC FORCE acting on the steel disk is computed below.

    // This field will hold the x and y component of the magnetic forces:
    field magforce("h1xy");

    // The magnetic force is projected on field 'magforce' on the steel region.
    // This is done with a formulation of the type dof*tf - force calculation = 0.
    formulation forceprojection;

    forceprojection += integral(core, dof(magforce)*tf(magforce));
    // The force term integral must be performed on all elements in the steel region AND in the ELEMENT LAYER AROUND.
    // This is obtained by considering the elements on the whole domain 'wholedomain'. Since the force must only be
    // calculated on the steel disk, the test functions are only selected on the steel (this is done with tf(..., steel)).
    forceprojection += integral(wholedomain, - predefinedmagnetostaticforce(grad(tf(magforce, core)), -grad(phi), mu));

    forceprojection.generate();
    vec solf = solve(forceprojection.A(), forceprojection.b());
    magforce.setdata(wholedomain, solf);

    std::cout << "Force acting on the steel disk (fx, fy) = (" << compx(magforce).integrate(core, 5) << ", " << compy(magforce).integrate(core, 5) << ") N per unit depth" << std::endl;

    // Code validation line. Can be removed.
    std::cout << (magfieldnorm[0] < 64963.8 && magfieldnorm[0] > 64963.6);

}

int main(void)
{
    SlepcInitialize(0,{},0,0);

    sparselizard();

    SlepcFinalize();

    return 0;
}

