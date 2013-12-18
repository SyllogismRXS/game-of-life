#ifndef GOL_H_
#define GOL_H_
/// ---------------------------------------------------------------------------
/// @file GOL.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2013-12-18 01:20:21 syllogismrxs>
///
/// @version 1.0
/// Created: 26 Nov 2013
///
/// ---------------------------------------------------------------------------
/// @section LICENSE
/// 
/// The MIT License (MIT)  
/// Copyright (c) 2012 Kevin DeMarco
///
/// Permission is hereby granted, free of charge, to any person obtaining a 
/// copy of this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation 
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the 
/// Software is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in 
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
/// DEALINGS IN THE SOFTWARE.
/// ---------------------------------------------------------------------------
/// @section DESCRIPTION
/// 
/// The GOL class ...
/// 
/// ---------------------------------------------------------------------------

#include <boost/multi_array.hpp>
#include <cassert>

#include <vector>

typedef enum Cost{
     Zero     = 0,
     Straight = 10,
     Diagonal = 14
} Cost_t;


template <class T>
class Point
{
public:
Point() : x(-1), y(-1) { }
Point(T xIn, T yIn) : x(xIn), y(yIn) { }
     T x;
     T y;

          
     double euclidean_distance(Point p)
     {
          double result;
          result = sqrt( pow((x-p.x),2) + pow(y-p.y,2) );
          return result;
     }
                    
     Point<T> operator+(const Point<T> &other)
     {
          return Point<T>(this->x + other.x, this->y + other.y);
     }
          
     Point<T> operator-(const Point<T> &other)
     {
          Point<T> point;
          point.x = this->x - other.x;
          point.y = this->y - other.y;
          return point;
     }
     
     Point<T> operator*(const double &other)
     {
          return Point<T>(this->x * other, this->y * other);
     }

     Point<T> operator*(const Point<T> &other)
     {
          return Point<T>(this->x * other.x, this->y * other.y);
     }

     Point<T> absolute()
     {
          return Point<T>(abs(this->x), abs(this->y));
     }

     bool operator==(const Point<T> &other) const
     {
          return (this->x == other.x) && (this->y == other.y);
     }
          
     bool operator!=(const Point<T> &other) const
     {
          return !(*this == other);
     }
          
     bool operator<(const Point<T> &rhs)
     {
          return (this->p1.x < rhs.x) || (this->p1.x == rhs.x && this->p1.y < rhs.y);
     }                    

};        

Point<double> add_points(const Point<double> &p1, const Point<int> &p2);
Point<double> sub_points(const Point<int> &p1, const Point<double> &p2);

class Direction {
public:
     enum Compass{
          N = 0,
          NE,
          E,
          SE,
          S,
          SW,
          W,
          NW
     };
          
     Cost_t cost_;
     Point<int> point_;
     Compass dir_;

     Point<int> point() { return point_; }
     Cost_t cost() { return cost_; }
     Compass dir() { return dir_; }

     Direction(Direction::Compass dir, Cost_t cost, Point<int> point) 
     {
          dir_ = dir;
          cost_ = cost;
          point_ = point;
     }
};

class Node
{     
public:
     typedef enum Grid{
          empty = 0,
          occupied,
          invalid
     }Grid_t;

     Point<int> & point() { return point_; }
     Grid_t grid_type() { return grid_type_; }
     void set_grid_type(Grid_t type) { grid_type_ = type; next_grid_type_ = type; }
     void set_next_grid_type(Grid_t type) { next_grid_type_ = type; }

     void update_grid_type() { grid_type_ = next_grid_type_; }

     Point<double> add_points(const Point<double> &p1, const Point<int> &p2)
     {
          Point<double> result;
          result.x = p1.x + (double)p2.x;
          result.y = p1.y + (double)p2.y;
          return result;
     }

     Point<double> sub_points(const Point<int> &p1, const Point<double> &p2)
     {
          Point<double> result;
          result.x = (double)p1.x - p2.x;
          result.y = (double)p1.y - p2.y;
          return result;
     }

     Node(Point<int> point) : point_(point) { }
     
     Node(int x, int y)
     {          
          point_.x = x;
          point_.y = y;
     }

     void reset()
     {
     }
     
     bool operator<(const Node &other) 
     {
          return false;
     }

protected:
     Point<int> point_;
     Grid_t grid_type_;
     Grid_t next_grid_type_;
private:     
};


class GOL {
public:
     GOL(int x_width, int y_height);
     ~GOL();
     
     std::vector<Direction> directions_;

     int x_width() const;
     int y_height() const;
     Node & at(int x, int y) const;
     
     void randomize();
     void step();

     bool valid(int x, int y);

protected:

     int neighbor_count(int x, int y);

private:
     int count_;

     int x_width_;
     int y_height_;
     
     typedef boost::multi_array<Node*, 2> array_type;
     typedef array_type::index index;
     array_type map_;
};

std::ostream& operator<<(std::ostream& os, const GOL& obj);

#endif
