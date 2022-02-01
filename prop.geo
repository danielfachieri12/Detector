// Gmsh project created on Thu Jan 20 19:42:44 2022
//+
// contador de tentativas : 24
// unidades em milimetros
ref = 4;
r = 0.5;     //raio do fio
R = 33.5;  // raio da latinha
D = 168;   // altura da latinha
Point(1) = {0, 0, 0, ref};
Point(2) = {0,0,D,ref};
Point(3) = {r,0,0,0.6}; 
Point(4) = {-r,0,0,0.6}; 
Point(5) = {R,0,0,ref};
Point(6) = {-R,0,0,ref};
Point(7) = {-R,0,D,ref};
Point(8) = {r,0,D,0.6};
Point(9) = {-r,0,D,0.6};
Point(10) = {R,0,D,ref};
//+
Circle(1) = {7, 2, 10};
//+
Circle(2) = {10, 2, 7};
//+
Circle(3) = {9, 2, 8};
//+
Circle(4) = {8, 2, 9};
//+
Circle(5) = {6, 1, 5};
//+
Circle(6) = {5, 1, 6};
//+
Circle(7) = {4, 1, 3};
//+
Circle(8) = {3, 1, 4};
//+
Line(9) = {8, 3};
//+
Line(10) = {4, 9};
//+
Curve Loop(1) = {2, 1};
//+
Line(11) = {10, 10};
//+
Line(12) = {5, 10};
//+
Line(13) = {7, 6};
//+
Curve Loop(2) = {2, 13, -6, 12};
//+
Surface(1) = {2};
//+
Curve Loop(3) = {12, -1, 13, 5};
//+
Surface(2) = {3};
//+
Curve Loop(4) = {4, -10, -8, -9};
//+
Surface(3) = {4};
//+
Curve Loop(5) = {9, -7, 10, 3};
//+
Surface(4) = {5};
//+
Curve Loop(6) = {4, 3};
//+
Plane Surface(5) = {1, 6};
//+
Curve Loop(7) = {6, 5};
//+
Curve Loop(8) = {8, 7};
//+
Plane Surface(6) = {7, 8};
//+
Surface Loop(1) = {1, 5, 2, 6, 4, 3};
//+
Volume(1) = {1};
//+
Physical Surface(14) = {1, 2};
//+
Physical Surface(15) = {5, 6};
//+
Physical Surface(16) = {3, 4};
//+
Physical Volume(17) = {1};
//+
Plane Surface(7) = {6};
//+
Plane Surface(8) = {8};
//+
Physical Surface(18) = {7};
//+
Physical Surface(19) = {8};
//+
Surface Loop(2) = {3, 4, 7, 8};
//+
Volume(2) = {2};
//+
Physical Volume(18) = {2};
