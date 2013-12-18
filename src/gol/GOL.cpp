#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "GOL.h"

using std::cout;
using std::endl;

GOL::GOL(int x_width, int y_height)
     : x_width_(x_width), y_height_(y_height)
{
     // Create a Node for each element in the map
     map_.resize(boost::extents[x_width_][y_height_]);
     for (int x = 0 ; x < x_width_; x++) {
          for (int y = 0; y < y_height_; y++) {
               if (map_[x][y] == NULL) {
                    map_[x][y] = new Node(x,y);
               } else {
                    map_[x][y]->reset();
               }                   
          }
     }

     directions_.push_back(Direction(Direction::N,Straight,Point<int>(0,1)));
     directions_.push_back(Direction(Direction::NE,Diagonal,Point<int>(1,1)));
     directions_.push_back(Direction(Direction::E,Straight,Point<int>(1,0)));
     directions_.push_back(Direction(Direction::SE,Diagonal,Point<int>(1,-1)));
     directions_.push_back(Direction(Direction::S,Straight,Point<int>(0,-1)));
     directions_.push_back(Direction(Direction::SW,Diagonal,Point<int>(-1,-1)));
     directions_.push_back(Direction(Direction::W,Straight,Point<int>(-1,0)));
     directions_.push_back(Direction(Direction::NW,Diagonal,Point<int>(-1,1)));
}

GOL::~GOL()
{
     for (int x = 0 ; x < x_width_; x++) {
          for (int y = 0; y < y_height_; y++) {
               if (map_[x][y] != NULL) {
                    delete map_[x][y];
               }                   
          }
     } 
}

int GOL::x_width() const
{
     return x_width_;
}

int GOL::y_height() const
{
     return y_height_;
}

Node & GOL::at(int x, int y) const
{
     return *(map_[x][y]);
}

void GOL::randomize()
{
     srand (time(NULL));
     int num = 0;
     
     for (int x = 0; x < x_width_; x++) {
          for (int y = 0; y < y_height_; y++) {
               num = rand() % 10 + 1;
               if (num >= 8) {
                    map_[x][y]->set_grid_type(Node::occupied);
               } else {
                    map_[x][y]->set_grid_type(Node::empty);
               }               
          }
     }
}

void GOL::step()
{
     for (int x = 0; x < x_width_; x++) {
          for (int y = 0; y < y_height_; y++) {
               int neighbors = this->neighbor_count(x,y);
               if (neighbors < 2) {
                    map_[x][y]->set_next_grid_type(Node::empty);
               } else if (map_[x][y]->grid_type() == Node::empty && neighbors == 3) {
                    map_[x][y]->set_next_grid_type(Node::occupied);
               } else if (neighbors == 2 || neighbors == 3) {
                    // nothing happens
               } else if (neighbors > 3) {
                    map_[x][y]->set_next_grid_type(Node::empty);
               }
          }
     }

     for (int x = 0; x < x_width_; x++) {
          for (int y = 0; y < y_height_; y++) {
               map_[x][y]->update_grid_type();
          }
     }
}

bool GOL::valid(int x, int y)
{
     if(x >= 0 && y >= 0 && x < x_width_ && y < y_height_) {
          return true;
     } else {
          return false;
     }
}

int GOL::neighbor_count(int x, int y)
{
     int neighbors = 0;     
     
     std::vector<Direction>::iterator dir_it;
     for (dir_it = directions_.begin(); dir_it != directions_.end(); dir_it++) {
          Point<int> point;
          point = map_[x][y]->point() + dir_it->point();
          
          if (this->valid(point.x,point.y) &&
              map_[point.x][point.y]->grid_type() == Node::occupied) {
               neighbors++;
          }
     }        
     return neighbors;
}

std::ostream& operator<<(std::ostream& os, const GOL& obj)
{
     int x_width = obj.x_width();
     int y_height = obj.y_height();
     
     for (int x = 0; x < x_width; x++) {
          for (int y = 0; y < y_height; y++) {
               os << obj.at(x,y).grid_type() << " ";
          }
          os << std::endl;
     }
     return os;
}
