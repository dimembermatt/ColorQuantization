/**
 *	colorQuant.cpp
 *  for color quantization of images,
 *      using 'buckets' (bounding boxes) and median cut.
 *	Last Modified: 1/20/19
 *      1/20 - updated find kth largest, added swap, integrated median cut with
 *          consistently improved results
 *	Author: Matthew Yu
 **/
#include "colorQuant.h"
using namespace std;
#include <iostream>

bool Point::operator ==(const Point& rhs) const{
    if(x == rhs.x && y == rhs.y && z == rhs.z)
        return true;
    else
        return false;
}

int& Point::operator[](const int idx){
    switch(idx) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw "something";
    }
}

void Point::printPoint(){
    cout << x << "," << y << "," << z << endl;
}

/*----------------------------------------------------------------------------*/
BoundBox::BoundBox(){
    pos = {0, 0, 0};
    dims = {0, 0, 0};
}

BoundBox::BoundBox(Point position, Point dimensions){
    pos = position;
    dims = dimensions;
}

bool BoundBox::contains(Point p){
    return
       (p.x >= pos.x && p.x < pos.x + dims.x &&
        p.y >= pos.y && p.y < pos.y + dims.y &&
        p.z >= pos.z && p.z < pos.z + dims.z );
}

bool BoundBox::intersects(BoundBox b){
    return
      !(b.pos.x > pos.x + dims.x    ||
        b.pos.x + b.dims.x < pos.x  ||
        b.pos.y > pos.y + dims.y    ||
        b.pos.y + b.dims.y < pos.y  ||
        b.pos.z > pos.z + dims.z    ||
        b.pos.z + b.dims.z < pos.z  );
}

void BoundBox::printBoundBox(){
    cout << pos.x << "," << pos.y << "," << pos.z << "|" <<
        dims.x << "," << dims.y << "," << dims.z << endl;
}
/*----------------------------------------------------------------------------*/
//private
int Bucket::getIdx(Point pt){
    for(unsigned int i = 0; i < pts.size(); i++){
        if(pts[i] == pt)
            return i;
    }
    return -1;
}

void Bucket::swap(vector<int>& nums, int l, int r){
    int temp = nums[l];
    nums[l] = nums[r];
    nums[r] = temp;
}

/*Reginald Frank, A&M Jan 2019*/
int Bucket::findKthLargest(vector<int>& nums, int k, int cIdx) {
    k = nums.size()-k; //where the element would appear in a sorted array
    int L,R,l,r;
    L = 0;
    R = nums.size()-1;
    while(L < R){
        int p = rand()%(R-L+1)+L;
        swap(nums, p, L);
        l = L;
        r = R;
        while(l<r){
            while(pts[nums[r]][cIdx] > pts[nums[L]][cIdx])
                r--;
            if(l == r)
                break;
            while(pts[nums[l]][cIdx] <= pts[nums[L]][cIdx] && l < R)
                l++;
            if(l < r)
                swap(nums, l, r--);
            else if(r != R)
                l--;
        }
        swap(nums, l, L);
        if(k == l)
            return nums[l];
        if(k < l)
            R = l-1;
        else L = l+1;
    }
    return nums[L];
}

int Bucket::findMedian(int cIdx){
    int kthLargest = pts.size()/2;
    if(pts.size()%2 == 1)   //odd
        kthLargest++;

    //build array
    vector<int> idxArr;
    for(int i = 0; i < pts.size(); i++){
        idxArr.push_back(i);
    }

    return findKthLargest(idxArr, kthLargest, cIdx);
}

//public
Bucket::Bucket(BoundBox b, int c){
    boundingArea = b;
    BUCKET_CAPACITY = c;
}

bool Bucket::insert(Point pt){
    if((unsigned int) boundingArea.contains(pt) && pts.size() < BUCKET_CAPACITY){
        for(unsigned int i = 0; i < pts.size(); i++){ //don't add duplicates
            if(pt == pts[i])
                return true;
        }
        pts.push_back(pt);
        return true;
    }
    return false;
}

bool Bucket::remove(Point pt){
    int j = getIdx(pt);
    if(j != -1){
        //shift all points down (n op)
        pts.erase(pts.begin() + j);
        return true;
    }
    return false;
}

int Bucket::getNumPts(){
    return pts.size();
}

int Bucket::getCapacity(){
    return BUCKET_CAPACITY;
}

void Bucket::setCapacity(int capacity){
    BUCKET_CAPACITY = capacity;
}

BoundBox Bucket::getBoundingArea(){
    return boundingArea;
}

void Bucket::setBoundingArea(BoundBox b){
    boundingArea = b;
}

Point Bucket::getPoint(int idx){
    if(idx >= 0 && idx < BUCKET_CAPACITY)
        return pts[idx];
    return pts[0];
}

bool Bucket::split(Bucket &otherBucket){
    //don't run if other bucket has stuff (to be safe)
    if(otherBucket.getNumPts() == 0){
        BoundBox save = boundingArea;

        int i;
        // find the longest axis of Cube;
        for(i = 0; i < 3; i++){
            if(boundingArea.getDims()[i%3] >= boundingArea.getDims()[(i+1)%3] &&
                boundingArea.getDims()[i%3] >= boundingArea.getDims()[(i+2)%3]){
                //largest dim is found
                break;
            }
        }

        // find the median along this axis;
        // cut Cube at median to form CubeA, CubeB;
        Point pos;
        Point dim;
        for(int j = 0; j < 3; j++){
            if(j == i){
                //if along the cut axis, shift pos/cut dim
                int medIdx = findMedian(j);
                dim[j] = pts[medIdx][j] -  boundingArea.getPos()[j];
                pos[j] = boundingArea.getPos()[j] + dim[j];
            }else{
                pos[j] = boundingArea.getPos()[j];
                dim[j] = boundingArea.getDims()[j];
            }
        }
        Point otherDim = boundingArea.getDims(), selfDim = dim;
        otherDim[i] -= selfDim[i];
        BoundBox b = BoundBox(pos, otherDim);
        otherBucket.setBoundingArea(b);
        boundingArea.setDims(dim);  //start pos doesn't change

        // move points into other bucket
        for(i = 0; i < getNumPts(); i++){
            Point pt = pts[i];
            if(!boundingArea.contains(pt)){
                bool res = true;
                res = remove(pt);
                if(!res){
                    cout << "bad delete" << endl;
                    while(1){
                        int b = 0;
                    }
                }
                res = otherBucket.insert(pt);
                if(!res){
                    cout << "bad insert (splitting)" << endl;
                    pt.printPoint();
                    while(1){
                        int b = 0;
                    }
                }
                i--;
            }
        }
        return true;
    }
    return false;
}

bool Bucket::merge(Bucket &otherBucket){
    if(getNumPts() + otherBucket.getNumPts() < BUCKET_CAPACITY){
        //check if they intersect
        BoundBox other = otherBucket.getBoundingArea();
        if(boundingArea.intersects(other)){
            //adjust boundingArea of bucket
            Point pos, dim;
            for(int i = 0; i < 3; i++){
                if(boundingArea.getPos()[i] > other.getPos()[i]){
                    dim[i] = boundingArea.getPos()[i] + boundingArea.getDims()[i] -
                        other.getPos()[i];
                    pos[i] = other.getPos()[i];
                }else{
                    dim[i] = other.getPos()[i] + other.getDims()[i] -
                        boundingArea.getPos()[i];
                    pos[i] = boundingArea.getPos()[i];
                }
            }
            boundingArea.setPos(pos);
            boundingArea.setDims(dim);

            //move points into bucket
            for(int i = 0; i <= otherBucket.getNumPts(); i++){
                Point p = otherBucket.getPoint(i);
                bool res = true;
                res = insert(p);
                if(!res)
                    cout << "bad insert" << endl;
                otherBucket.remove(p);
                if(!res)
                    cout << "bad delete" << endl;
            }
            return true;
        }
    }
    return false;
}

void Bucket::getBucketContent(){
    for(int i = 0; i < getNumPts(); i++){
        pts[i].printPoint();
    }
}

Point Bucket::getColor(){
    Point p = {0, 0, 0};
    for(int i = 0; i < getNumPts(); i++){
        for(int j = 0; j < 3; j++){
            p[j] += pts[i][j];

        }
    }
    for(int j = 0; j < 3; j++){
        p[j] /= getNumPts();
    }
    return p;
}
