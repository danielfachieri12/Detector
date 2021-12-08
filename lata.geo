//+
a=10;
Point(1) = {0, 0, 0, 2.0};
//+
Point(2) = {0, 0, a*16.8, 2.0};
//+
Point(3) = {a*0.0365, 0, 0, 2.0};
//+
Point(4) = {a*-0.0365, 0, 0, 2.0};
//+
Point(5) = {a*-0.0365, 0, a*16.8, 2.0};
//+
Point(6) = {a*0.0365, 0, a*16.8, 2.0};
//+1
Point(7) = {a*3.35, 0, a*16.8, 2.0};
//+
Point(8) = {a*-3.35, 0, a*16.8, 2.0};
//+
Point(9) = {a*-3.35, 0, 0, 2.0};
//+
Point(10) = {a*3.35, 0, 0, 2.0};
//+
Circle(1) = {6, 2, 5};
//+
Circle(2) = {5, 2, 6};
//+
Circle(3) = {8, 2, 7};
//+
Circle(4) = {7, 2, 8};
//+
Circle(5) = {9, 1, 10};
//+
Circle(6) = {10, 1, 9};
//+
Circle(7) = {4, 1, 3};
//+
Circle(8) = {3, 1, 4};
//+
Line(9) = {7, 10};
//+
Line(10) = {6, 3};
//+
Line(11) = {5, 4};
//+
Line(12) = {8, 9};
//+
Curve Loop(1) = {10, 8, -11, -1};
//+
Surface(1) = {1};
//+
Curve Loop(2) = {10, -7, -11, 2};
//+
Surface(2) = {2};
//+
Curve Loop(3) = {9, 6, -12, -4};
//+
Surface(3) = {3};
//+
Curve Loop(4) = {9, -5, -12, 3};
//+
Surface(4) = {4};
//+
Curve Loop(5) = {4, 3};
//+
Curve Loop(6) = {1, 2};
//+
Plane Surface(5) = {5, 6};
//+
Curve Loop(7) = {6, 5};
//+
Curve Loop(8) = {8, 7};
//+
Plane Surface(6) = {7, 8};
//+
Surface Loop(1) = {3, 4, 6, 2, 1, 5};
//+
Volume(1) = {1};
//+
Physical Surface(13) = {3, 4};
//+
Physical Surface(14) = {1, 2};
//+
Physical Surface(15) = {5};
//+
Physical Surface(16) = {6};
//+
Physical Volume(17) = {1};
