// This mesh file is part of the "Cohomology" example of software "GetDP" (Patrick Dular and Christophe Geuzaine).
// Only minor adaptations were made to include it as a sparselizard example so all the credit for this great 
// geometry and mesh go to the above mentioned persons.



lc = 0.02; // Mesh characteristic length
lc2 = lc;
lc3 = 0;
front3d = 0; // Set to 1 if Frontal 3D mesh algorithm is used
nn = (1./lc)/4.; // Mesh subdivisions per turn, used with Frontal 3D

If(front3d == 1)
  Mesh.Algorithm3D = 4; // Frontal 3D
EndIf
Mesh.Optimize = 1;

DefineConstant
[
  turns = {5, Name "Geometry/Number of coil turns"},
  r = {0.11, Name "Geometry/Coil radius"},
  rc = {0.0005, Name "Geometry/Coil wire radius"},
  lb = {0.1, Name "Geometry/Infinite box width"}
  wx1 = {0.008, Name "Geometry/WX1"},
  wx2 = {0.003, Name "Geometry/WX2"},
  wx3 = {0.015, Name "Geometry/WX3"},
  wy1 = {0.003, Name "Geometry/WY1"},
  wy2 = {0.003, Name "Geometry/WY2"},
  wy3 = {0.008, Name "Geometry/WY3"},
  wy4 = {0.004, Name "Geometry/WY4"},
  wz1 = {0.008, Name "Geometry/WZ1"},
  wp = {0.0005, Name "Geometry/Wire padding"},
  pmwidth = {0.008,Name "Geometry/Permanent magnet width"},
  pmheight = {0.001,Name "Geometry/Permanent magnet height"},
  airgap = {0.0001, Name "Geometry/Air gap"},
  pmxpos = {0,Name "Geometry/Peramnent magnet pos X"},
  pmzpos = {0,Name "Geometry/Peramnent magnet pos Z"},
  pmholderheight = {0.001,Name "Geometry/Peramnent magnet holder height"}
];

// core
p = newp;
Point(p)    = {0                                                                 , wy1+wy2+wy3+wy4      , -wz1/2, lc2};
Point(p+1)  = {wx1                                                               , wy1 + wy2 + wy3 + wy4, -wz1/2, lc2};
Point(p+2)  = {wx1                                                               , wy2 + wy3 + wy4      , -wz1/2, lc2};
Point(p+3)  = {(wx1 + wx2) / 2                                                   , wy3 + wy4            , -wz1/2, lc2};
Point(p+4)  = {(wx1 + wx2) / 2                                                   , wy4                  , -wz1/2, lc2};
Point(p+5)  = {(wx1 + wx2) / 2 + wx3                                             , wy4                  , -wz1/2, lc2};
Point(p+6)  = {(wx1 + wx2) / 2 + wx3                                             , wy4+wy3              , -wz1/2, lc2};
Point(p+7)  = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2) / 2                           , wy4 + wy3+wy2        , -wz1/2, lc2};
Point(p+8)  = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2) / 2                           , wy4 + wy3 + wy2 + wy1, -wz1/2, lc2};
Point(p+9)  = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2) / 2 + wx1                     , wy1 + wy2 + wy3 + wy4, -wz1/2, lc2};
Point(p+10) = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2) / 2 + wx1                     , wy2 + wy3 + wy4      , -wz1/2, lc2};
Point(p+11) = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2)  + wx1                        , wy3 + wy4            , -wz1/2, lc2};
Point(p+12) = {(wx1 + wx2) / 2 + wx3 - (wx1 - wx2)  + wx1                        , 0                    , -wz1/2, lc2};
Point(p+13) = {(wx1 - wx2) / 2                                                   , 0                    , -wz1/2, lc2};
Point(p+14) = {(wx1 - wx2) / 2                                                   , wy4+wy3              , -wz1/2, lc2};
Point(p+15) = {0                                                                 , wy4 + wy3+wy2        , -wz1/2, lc2};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p+4};
Line(l+4) = {p+4,p+5};
Line(l+5) = {p+5,p+6};
Line(l+6) = {p+6,p+7};
Line(l+7) = {p+7,p+8};
Line(l+8) = {p+8,p+9};
Line(l+9) = {p+9,p+10};
Line(l+10) = {p+10,p+11};
Line(l+11) = {p+11,p+12};
Line(l+12) = {p+12,p+13};
Line(l+13) = {p+13,p+14};
Line(l+14) = {p+14,p+15};
Line(l+15) = {p+15,p};

ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3,l+4,l+5,l+6,l+7,l+8,l+9,l+10,l+11,l+12,l+13,l+14,l+15};
s = news;
Plane Surface(s) = {ll};
If(front3d == 1)
tmp[] = Extrude {0,0,wz1}{ Surface{s}; Layers{nn}; };
EndIf
If(front3d == 0)
tmp[] = Extrude {0,0,wz1}{ Surface{s}; };
EndIf
vol_core = tmp[1];

// coil 1
p = newp;
Point(p)=  {(wx1-wx2)/2, wy4, wz1/2+wp, lc};
Point(p+1)={(wx1-wx2)/2, wy4+rc  , wz1/2+wp, lc};
Point(p+2)={(wx1-wx2)/2, wy4+rc, wz1/2+wp+rc, lc};
Point(p+3)={(wx1-wx2)/2, wy4  , wz1/2+wp+rc, lc};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};
ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3};
s = news;
Plane Surface(s) = {ll};
tmp[] = {s};
vol_coil_1[] = {};
For j In {1:turns}
If(front3d == 1)
 // tmp[] = Extrude {  {0,wy3/turns/4,0},  {0,0,0} ,  {0,0,0} ,  Pi/2  }  { Surface {tmp[0]}; Layers {nn / 4}; };
EndIf
If(front3d == 0)
  tmp[] = Extrude { wx2,(wy3-rc)/turns/4,0}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1+wx2)/2,0,wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { 0,(wy3-rc)/turns/4,-wz1}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1+wx2)/2,0,-wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { -wx2,(wy3-rc)/turns/4,0}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1-wx2)/2,0,-wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { 0,(wy3-rc)/turns/4,wz1}{ Surface {tmp[0]}; };
    tmp[] = Extrude {  {0,1,0} ,  {(wx1-wx2)/2,0,wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
EndIf
  vol_coil_1[] += tmp[1];
EndFor

tmp[] = Extrude {0.0001, 0, 0} { Surface{tmp[0]}; };
vol_coil_1[] += tmp[1];
out_1 = tmp[0];
tmp[] = Extrude {-0.0001, 0, 0} { Surface{s}; };
vol_coil_1[] += tmp[1];
in_1 = tmp[0];


// coil 2
p = newp;
Point(p)=  {(wx1-wx2)/2+wx3+wx2, wy4, wz1/2+wp, lc};
Point(p+1)={(wx1-wx2)/2+wx3+wx2, wy4+rc  , wz1/2+wp, lc};
Point(p+2)={(wx1-wx2)/2+wx3+wx2, wy4+rc, wz1/2+wp+rc, lc};
Point(p+3)={(wx1-wx2)/2+wx3+wx2, wy4  , wz1/2+wp+rc, lc};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};
ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3};
s = news;
Plane Surface(s) = {ll};
tmp[] = {s};
vol_coil_2[] = {};
For j In {1:turns}
If(front3d == 1)
 // tmp[] = Extrude {  {0,wy3/turns/4,0},  {0,0,0} ,  {0,0,0} ,  Pi/2  }  { Surface {tmp[0]}; Layers {nn / 4}; };
EndIf
If(front3d == 0)
  tmp[] = Extrude { wx2,(wy3-rc)/turns/4,0}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1+wx2)/2+wx3+wx2,0,wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { 0,(wy3-rc)/turns/4,-wz1}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1+wx2)/2+wx3+wx2,0,-wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { -wx2,(wy3-rc)/turns/4,0}{ Surface {tmp[0]}; };
  tmp[] = Extrude {  {0,1,0} ,  {(wx1-wx2)/2+wx3+wx2,0,-wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
  tmp[] = Extrude { 0,(wy3-rc)/turns/4,wz1}{ Surface {tmp[0]}; };
    tmp[] = Extrude {  {0,1,0} ,  {(wx1-wx2)/2+wx3+wx2,0,wz1/2} ,   Pi/2   }   { Surface {tmp[0]}; };
EndIf
  vol_coil_2[] += tmp[1];
EndFor

tmp[] = Extrude {0.0001, 0, 0} { Surface{tmp[0]}; };
vol_coil_2[] += tmp[1];
out_2 = tmp[0];
tmp[] = Extrude {-0.0001, 0, 0} { Surface{s}; };
vol_coil_2[] += tmp[1];
in_2 = tmp[0];

// box
p = newp;
Point(p) = {-lb/2,-lb/2,-lb/2, lc3};
Point(p+1) = {lb/2,-lb/2,-lb/2, lc3};
Point(p+2) = {lb/2,lb/2,-lb/2, lc3};
Point(p+3) = {-lb/2,lb/2,-lb/2, lc3};
Point(p+4) = {-lb/2,-lb/2,lb/2, lc3};
Point(p+5) = {lb/2,-lb/2,lb/2, lc3};
Point(p+6) = {lb/2,lb/2,lb/2, lc3};
Point(p+7) = {-lb/2,lb/2,lb/2, lc3};
l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};
Line(l+4) = {p+4,p+5};
Line(l+5) = {p+5,p+6};
Line(l+6) = {p+6,p+7};
Line(l+7) = {p+7,p+4};
Line(l+8) = {p, p+4};
Line(l+9) = {p+1, p+5};
Line(l+10) = {p+2, p+6};
Line(l+11) = {p+3, p+7};

ll = newll;
Line Loop(ll) = Boundary {Surface{in_1}; };
Line Loop(ll+1) = {l+8, -(l+7), -(l+11), l+3};
Line Loop(ll+2) = Boundary {Surface{out_1}; };
Line Loop(ll+3) = {l+9, l+5, -(l+10), -(l+1)};
Line Loop(ll+4) = {l,l+1,l+2,l+3};
Line Loop(ll+5) = {l+4,l+5,l+6,l+7};
Line Loop(ll+6) = {l+2, l+11, -(l+6), -(l+10)};
Line Loop(ll+7) = {l, l+9, -(l+4), -(l+8)};
Line Loop(ll+8) = Boundary {Surface{in_2}; };
Line Loop(ll+9) = Boundary {Surface{out_2}; };
s = news;
tmp[] = {ll+1, ll};

Plane Surface(s) = tmp[];
tmp[] = {ll+3};
tmp[] += ll+2;

Plane Surface(s+1) = tmp[];
Plane Surface(s+2) = {ll+4};
Plane Surface(s+3) = {ll+5};
Plane Surface(s+4) = {ll+6};
Plane Surface(s+5) = {ll+7};

sl = newsl;
skin_coil_1[] = CombinedBoundary{ Volume{vol_coil_1[]}; };
skin_coil_1[] -= {in_1, out_1};
Surface Loop(sl) = {s:s+5,skin_coil_1[]};
Surface Loop(sl+1) = CombinedBoundary{ Volume{vol_core[]}; };
v = newv;
Volume(v) = {sl, sl+1};

sl = newsl;
skin_coil_2[] = CombinedBoundary{ Volume{vol_coil_2[]}; };
skin_coil_2[] -= {in_2, out_2};
Surface Loop(sl) = {s:s+5,skin_coil_2[]};
Surface Loop(sl+1) = CombinedBoundary{ Volume{vol_core[]}; };
v = newv;
Volume(v) = {sl, sl+1};


//permanent magnet 1
p = newp;
Point(p)    = {0   +pmxpos                                                               , wy1+wy2+wy3+wy4+airgap, -pmwidth/2+pmzpos, lc2};
Point(p+1)  = {pmwidth        +pmxpos                                                        , wy1+wy2+wy3+wy4+airgap , -pmwidth/2+pmzpos, lc2};
Point(p+2)  = {pmwidth       +pmxpos                                                         , wy1+wy2+wy3+wy4+airgap       , pmwidth/2+pmzpos, lc2};
Point(p+3)  = {0            +pmxpos                                      , wy1+wy2+wy3+wy4+airgap             , pmwidth/2+pmzpos, lc2};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};

ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3};
s = news;
Plane Surface(s) = {ll};
If(front3d == 1)
tmp[] = Extrude {0,pmheight,0}{ Surface{s}; Layers{nn}; };
EndIf
If(front3d == 0)
tmp[] = Extrude {0,pmheight,0}{ Surface{s}; };
EndIf
vol_pm_1 = tmp[1];

//permanent magnet 2
p = newp;
Point(p)    = {0  +wx2    +wx3+pmxpos                                                           , wy1+wy2+wy3+wy4+airgap, -pmwidth/2+pmzpos, lc2};
Point(p+1)  = {pmwidth+wx2 +wx3 +pmxpos                                                             , wy1+wy2+wy3+wy4+airgap , -pmwidth/2+pmzpos, lc2};
Point(p+2)  = {pmwidth +wx2  +wx3    +pmxpos                                                        , wy1+wy2+wy3+wy4+airgap       , pmwidth/2+pmzpos, lc2};
Point(p+3)  = {0      +wx2   +wx3    +pmxpos                                    , wy1+wy2+wy3+wy4+airgap             , pmwidth/2+pmzpos, lc2};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};

ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3};
s = news;
Plane Surface(s) = {ll};
If(front3d == 1)
tmp[] = Extrude {0,pmheight,0}{ Surface{s}; Layers{nn}; };
EndIf
If(front3d == 0)
tmp[] = Extrude {0,pmheight,0}{ Surface{s}; };
EndIf
vol_pm_2 = tmp[1];


//permanent magnet holder
p = newp;
Point(p)    = {0 + pmxpos                                                           , wy1+wy2+wy3+wy4+airgap+pmheight, -pmwidth/2+pmzpos, lc2};
Point(p+1)  = {pmwidth+wx2 +wx3 +pmxpos                                                             , wy1+wy2+wy3+wy4+airgap+pmheight , -pmwidth/2+pmzpos, lc2};
Point(p+2)  = {pmwidth +wx2  +wx3    +pmxpos                                                        , wy1+wy2+wy3+wy4+airgap+pmheight       , pmwidth/2+pmzpos, lc2};
Point(p+3)  = {0        +pmxpos                                    , wy1+wy2+wy3+wy4+airgap+pmheight             , pmwidth/2+pmzpos, lc2};

l = newl;
Line(l) = {p,p+1};
Line(l+1) = {p+1,p+2};
Line(l+2) = {p+2,p+3};
Line(l+3) = {p+3,p};

ll = newll;
Line Loop(ll) = {l,l+1,l+2,l+3};
s = news;
Plane Surface(s) = {ll};
If(front3d == 1)
tmp[] = Extrude {0,pmholderheight,0}{ Surface{s}; Layers{nn}; };
EndIf
If(front3d == 0)
tmp[] = Extrude {0,pmholderheight,0}{ Surface{s}; };
EndIf
vol_pm_holder = tmp[1];


COIL_1 = 1;
COIL_2 = 2;
CORE = 3;
AIR = 4;
SKIN_COIL_1 = 5;
SKIN_COIL_2 = 6;
SKIN_CORE = 7;
PM_1 = 8;
PM_2 = 9;
PM_HOLDER = 10;
IN_1 = 11;
IN_2 = 12;
OUT_1 = 13;
OUT_2 = 14;
INF = 15;
ZERO_POTENTIAL = 16;

Physical Volume(COIL_1) = {vol_coil_1[]};
Physical Volume(COIL_2) = {vol_coil_2[]};
Physical Volume(CORE) = {vol_core[]};
Physical Volume(AIR) = {v};
Physical Surface(SKIN_COIL_1) = {vol_coil_1[]};
Physical Surface(SKIN_COIL_2) = {vol_coil_2[]};
Physical Surface(SKIN_CORE) = CombinedBoundary{ Volume{vol_core[]}; };
Physical Volume(PM_1) = {vol_pm_1[]};
Physical Volume(PM_2) = {vol_pm_2[]};
Physical Volume(PM_HOLDER) = {vol_pm_holder[]};
Physical Surface(IN_1) = in_1;
Physical Surface(IN_2) = in_2;
Physical Surface(OUT_1) = out_1;
Physical Surface(OUT_2) = out_2;
Physical Surface(INF) = {s:s+5};

