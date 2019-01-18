/**
 *	tester.cpp
 *  for testing classes.
 *	Last Modified: 1/16/19
 *	Author: Matthew Yu
 **/

#include "colorQuant.cpp"
#include <iostream>

using namespace std;

int main(){
    Point p1 = {0, 0, 0};
    Point d1 = {256, 256, 256};
    Point p4 = {150, 200, 255};
    Point d2 = {50, 150, 205};

    Point p2 = {50, 50, 0};
    Point p3 = {50, 50, 0};
    Point p5 = {50, 50, 255};

    BoundBox b = BoundBox(p1, d1);
    BoundBox b2 = BoundBox(p4, d2);

    // cout << "\nContains test" << endl;
    // if(b.contains(p2))
    //     cout << "b contains p2" << endl;

    // if(!b2.contains(p2))
    //     cout << "b2 ! contains p2" << endl;
    //
    // cout << "\nIntersection test " << endl;
    // if(b.intersects(b2))
    //     cout << "b intersects with b2" << endl;
    // else
    //     cout << "b ! intersects with b2" << endl;

    b.printBoundBox();
    b2.printBoundBox();

    Bucket bu = Bucket(b);
    Bucket bu2 = Bucket(b2);

    cout << "\nInsertion test" << endl;
    cout << bu.insert(p2) << endl;
    cout << bu.insert(p3) << endl;
    cout << bu.insert(p5) << endl;

    BoundBox out;

    bu.getBucketContent();
    cout << "---------------"<< endl;
    // bu2.getBucketContent();
    cout << "-bucket dim (A|B)-\n";
    out = bu.getBoundingArea();
    out.printBoundBox();
    // out = bu2.getBoundingArea();
    // out.printBoundBox();

    // cout << "\nMerge test" << endl;
    // bu.merge(bu2);
    // bu.getBucketContent();
    // cout << "---------------"<< endl;
    // bu2.getBucketContent();
    // cout << "-bucket dim (A:merged|B)-\n";
    // out = bu.getBoundingArea();
    // out.printBoundBox();
    // out = bu2.getBoundingArea();
    // out.printBoundBox();
    //
    // cout << "\nSplit test" << endl;
    // bu.split(bu2);
    // bu.getBucketContent();
    // cout << "---------------"<< endl;
    // bu2.getBucketContent();
    //
    // cout << "-bucket dim (A:split|B:new)-\n";
    // out = bu.getBoundingArea();
    // out.printBoundBox();
    // out = bu2.getBoundingArea();
    // out.printBoundBox();

    cout << "\nColor test" << endl;
    Point c = bu.getColor();
    c.printPoint();
}
