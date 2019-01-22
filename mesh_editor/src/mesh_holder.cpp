#include "mesh_holder.h"

#include <qmath.h>
#include <mesh/mesh.h>
#include <traces.h>
#include <include/mesh_holder.h>


MeshHolder::MeshHolder()
        : m_count(0) {


    loadModel("../../models/halbacharray.msh");
}


void MeshHolder::loadModel(char *path) {


    // The domain regions as defined in 'disk.geo':
    int vol = 1, sur = 2, top = 3;


    mesh mymesh("../../models/halbacharray.msh");

    physicalregions *myphysregs = universe::mymesh->getphysicalregions(); // This holds all individual physical region objects

    // Get the list of all physical regions:
    std::vector<int> allphysregnumbers = myphysregs->getallnumbers();

    // Loop on all physical region numbers:
    for (int i = 0; i < allphysregnumbers.size(); i++) {
        int curphysregnum = allphysregnumbers[i];
        // Get the object corresponding to the current physical region number:
        physicalregion *curphysreg = myphysregs->get(curphysregnum);

        // Get the list of all element indexes of every element type.
        // 'elemlist' at index 'j' lists all elements of type number j in the current physical region.
        // You can find which element type number corresponds to what type (point, line, triangle, quad,...) in the "element.h" header.
        std::vector<std::vector<int>> *elemlist = curphysreg->getelementlist();

        // You can also get extra information on the physical region, like e.g. the dimension of the elements it holds with:
        int elemdim = curphysreg->getelementdimension(); // All elements are of the same dimension in a given physical region

        elements *myelements = universe::mymesh->getelements();

        //info_msg("phis reg: ", elemdim);

        for (int typenum = 0; typenum <= 7; typenum++) {
            //info_msg("type: ",typenum," sz: ",(*elemlist)[typenum].size());
            // Iterate on all elements of the given type:
            for (int i = 0; i < (*elemlist)[typenum].size(); i++) {
                std::vector<double> xcoordselementnodes = myelements->getnodecoordinates(typenum, i, 0);
                std::vector<double> ycoordselementnodes = myelements->getnodecoordinates(typenum, i, 1);
                std::vector<double> zcoordselementnodes = myelements->getnodecoordinates(typenum, i, 2);

                if (!xcoordselementnodes.empty()) {
                    switch (typenum) {
                        case 0:
                            addPoint(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 1:
                            addLine(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 2:
                            addTriangle(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 3:
                            addQuadrangle(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 4:
                            addTetrahedra(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 5:
                            addHexahedra(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 6:
                            addPisms(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;
                        case 7:
                            addPyramids(xcoordselementnodes, ycoordselementnodes, zcoordselementnodes);
                            break;

                    }
                }
            }
        }
    }

    // m_data.resize(2500 * 6);

//    const GLfloat x1 = +0.0 in my 6f;
//    const GLfloat y1 = -0.14f;
//    const GLfloat x2 = +0.14f;
//    const GLfloat y2 = -0.06f;
//    const GLfloat x3 = +0.08f;
//    const GLfloat y3 = +0.00f;
//    const GLfloat x4 = +0.30f;
//    const GLfloat y4 = +0.22f;
//
//    quad(x1, y1, x2, y2, y2, x2, y1, x1);
//    quad(x3, y3, x4, y4, y4, x4, y3, x3);
//
//    extrude(x1, y1, x2, y2);
//    extrude(x2, y2, y2, x2);
//    extrude(y2, x2, y1, x1);
//    extrude(y1, x1, x1, y1);
//    extrude(x3, y3, x4, y4);
//    extrude(x4, y4, y4, x4);
//    extrude(y4, x4, y3, x3);
//
//    const int NumSectors = 100;
//
//    for (int i = 0; i < NumSectors; ++i) {
//        GLfloat angle = (i * 2 * M_PI) / NumSectors;
//        GLfloat angleSin =  in my qSin(angle);
//        GLfloat angleCos = qCos(angle);
//        const GLfloat x5 = 0.30f * angleSin;
//        const GLfloat y5 = 0.30f * angleCos;
//        const GLfloat x6 = 0.20f * angleSin;
//        const GLfloat y6 = 0.20f * angleCos;
//
//        angle = ((i + 1) * 2 * M_PI) / NumSectors;
//        angleSin = qSin(angle);
//        angleCos = qCos(angle);
//        const GLfloat x7 = 0.20f * angleSin;
//        const GLfloat y7 = 0.20f * angleCos;
//        const GLfloat x8 = 0.30f * angleSin;
//        const GLfloat y8 = 0.30f * angleCos;
//
//        quad(x5, y5, x6, y6, x7, y7, x8, y8);
//
//        extrude(x6, y6, x7, y7);
//        extrude(x8, y8, x5, y5);
//    }

}


void MeshHolder::add(const QVector3D &v, const QVector3D &n) {
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void MeshHolder::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4) {
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x4, y4, -0.05f), n);
    add(QVector3D(x2, y2, -0.05f), n);

    add(QVector3D(x3, y3, -0.05f), n);
    add(QVector3D(x2, y2, -0.05f), n);
    add(QVector3D(x4, y4, -0.05f), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, 0.05f), n);
    add(QVector3D(x1, y1, 0.05f), n);
    add(QVector3D(x2, y2, 0.05f), n);

    add(QVector3D(x2, y2, 0.05f), n);
    add(QVector3D(x3, y3, 0.05f), n);
    add(QVector3D(x4, y4, 0.05f), n);
}

void MeshHolder::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);

    add(QVector3D(x2, y2, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
}

void MeshHolder::addPoint(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {
    std::cout<<"addPoint\n["<<xchords.at(0)<< " "<<ychords.at(0)<< " "<<zchords.at(0)<<"]\n";
}

void MeshHolder::addLine(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {
    std::cout<<"addLine\n["<<xchords.at(0)<< " "<<ychords.at(0)<< " "<<zchords.at(0)<<"],"<<
             "["<<xchords.at(1)<< " "<<ychords.at(1)<< " "<<zchords.at(1)<<"]\n";

}
void MeshHolder::addTriangle(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {
    std::cout<<"addTriangle\n["<<xchords.at(0)<< " "<<ychords.at(0)<< " "<<zchords.at(0)<<"],"<<
             "["<<xchords.at(1)<< " "<<ychords.at(1)<< " "<<zchords.at(1)<<"],"<<
             "["<<xchords.at(2)<< " "<<ychords.at(2)<< " "<<zchords.at(2)<<"]\n";

    m_data.resize(m_count + 18);

    auto A = QVector3D(xchords.at(0), ychords.at(0), zchords.at(0));
    auto B = QVector3D(xchords.at(1), ychords.at(1), zchords.at(1));
    auto C = QVector3D(xchords.at(2), ychords.at(2), zchords.at(2));

    auto q = A - B;
    auto p = C - B;

    auto n = QVector3D::crossProduct(q, p);
    add(A, n);
    add(B, n);
    add(C, n);
}


void MeshHolder::addQuadrangle(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {
    std::cout<<"addQuadrangle\n["<<xchords.at(0)<< " "<<ychords.at(0)<< " "<<zchords.at(0)<<"],"<<
             "["<<xchords.at(1)<< " "<<ychords.at(1)<< " "<<zchords.at(1)<<"],"<<
             "["<<xchords.at(2)<< " "<<ychords.at(2)<< " "<<zchords.at(2)<<"],"<<
             "["<<xchords.at(3)<< " "<<ychords.at(3)<< " "<<zchords.at(3)<<"]\n";
}

void MeshHolder::addTetrahedra(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {

}

void MeshHolder::addHexahedra(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {

}

void MeshHolder::addPisms(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {

}

void MeshHolder::addPyramids(std::vector<double> xchords, std::vector<double> ychords, std::vector<double> zchords) {

}
