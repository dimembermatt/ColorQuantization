/**
 *	colorQuant.h
 *  for color quantization of images,
 *      using 'buckets' (bounding boxes) and median cut.
 *  Note: median cut currently provides worse results compared to dim/2,
 *      WIP and unused
 *	Last Modified: 1/19/19
 *	Author: Matthew Yu
 **/
#ifndef _COLORQUANT_H
#define _COLORQUANT_H
#include <vector>
using std::vector;


class Point{
    public:
        int x;  //r
        int y;  //g
        int z;  //b
        bool operator ==(const Point& rhs) const;
        int& operator[](const int idx);
        void printPoint();
};

class BoundBox{
    private:
        //x|length|r, y|width|g, z|depth|b
        Point pos;
        Point dims;

    public:
        BoundBox();
        BoundBox(Point position, Point dimensions);

        /**
         *  @funct: checks if point is contained in box
         *  @param: Point pt - color to put into bucket
         *  @return: bool - TRUE IF CONTAINS
         **/
        bool contains(Point p);

        /**
         *  @funct: checks if box intersects with another box
         *  @param: BoundBox b - box to check against
         *  @return: bool - TRUE IF INTERSECTS
         **/
        bool intersects(BoundBox b);

        Point getPos(){
            return pos;
        }

        Point getDims(){
            return dims;
        }

        void setPos(Point p){
            pos = p;
        }

        void setDims(Point p){
            dims = p;
        }

        void printBoundBox();
};

class Bucket{
	private:
        int BUCKET_CAPACITY;
        BoundBox boundingArea;
        vector<Point> pts;

        /**
         *  @funct: checks if point is in the bucket
         *  @param: Point pt - color to check
         *  @return: int - zero idx of pt in pts, -1 elsewise
         **/
        int getIdx(Point pt);

        /**
         *  @funct: finds the kth largest number in a set of numbers
         *  @param: vector<int>& nums, set of numbers
         *      in this context, a set of indexes -accessing the idx val
         *  @param: int k - look for the kth largest value
         *  @param: int cIdx - compare the color at cIdx of each point
         *  @return: int - zero idx of kth largest number in the set
         *  @note: UNUSED - QUALITY LOSS COMPARED TO DIM/2
         **/
        int findKthLargest(vector<int>& nums, int k, int cIdx);

        /**
         *  @funct: finds the median of the points in the bucket
         *  @param: int cIdx - part of the Point (r|g|b)
         *  @return: int - zero idx of pt in pts, -1 elsewise
         *  @note: UNUSED - QUALITY LOSS COMPARED TO DIM/2
         **/
        int findMedian(int cIdx);
	public:
		Bucket(BoundBox b, int c);

        /**
         *  @funct: insert a color into the bucket
         *  @param: Point pt - color to put into bucket
         *  @return: bool - true if successful insert
         **/
        bool insert(Point pt);

        /**
         *  @funct: remove a color from the bucket
         *  @param: Point pt - color to take from bucket
         *  @return: bool - true if successful delete
         *  @note:  no expectations of currently using but implement anyway
         **/
        bool remove(Point pt);

        /**
         *  @funct: returns number of colors in bucket
         *  @return: int - number of colors in bucket
         *  @note: for determining whether to split the bucket
         **/
        int getNumPts();

        /**
         *  @funct: returns max allowed colors in bucket
         *  @return: int - max number of colors in bucket
         **/
        int getCapacity();

        /**
         *  @funct: sets max number of colors in bucket
         *  @return: int - max number of colors in bucket
         **/
        void setCapacity(int capacity);

        /**
         *  @funct: returns bounding box of bucket
         *  @return: BoundBox - the bounding box
         *  @note: for merging buckets
         **/
        BoundBox getBoundingArea();

        /**
         *  @funct: sets bounding box of bucket
         *  @note: for splitting buckets
         **/
        void setBoundingArea(BoundBox b);

        /**
         *  @funct: gets point at idx in bucket
         *  @return: Point copy of point data
         *  @precondition: idx is valid in bucket (else return 0th idx)
         *  @note: for merging buckets
         **/
        Point getPoint(int idx);

        /**
         *  @funct: Splits the current bucket into two buckets along the median
         *  @param: Bucket& otherBucket - other bucket to put points in
         *  @return: bool - true if successful split
         *  @pre_condition: other bucket is EMPTY
         **/
        bool split(Bucket &otherBucket);

        /**
         *  @funct: Merges two buckets into one
         *  @param: Bucket& otherBucket - other bucket to take points from
         *  @return: bool - true if successful merge
         *  @pre_condition: sum of both buckets is < NODE_CAPACITY
         *  @post_condition: otherBucket is deleted after use
         **/
        bool merge(Bucket &otherBucket);

        /**
         *  @funct: prints all Points in the bucket
         **/
        void getBucketContent();

        /**
         *  @funct: gets mean quantized color from bucket
         *  @return: Point - color of bucket
         **/
        Point getColor();
};


#endif
