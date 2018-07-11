//
//  RandomHomology.hpp
//  BitTests
//
//  Created by Bill Varcho on 2/24/16.
//  Copyright © 2016 Bill Varcho. All rights reserved.
//

#ifndef RandomHomology_hpp
#define RandomHomology_hpp
#include "Utilities.hpp"
#include <gudhi/Alpha_complex.h>
// to construct a simplex_tree from alpha complex
#include <gudhi/Simplex_tree.h>
#include <CGAL/Epick_d.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Alpha_shape_3.h>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <limits>  // for numeric limits
#include <fstream>
#include <list>
#include <cassert>
//using Kernel = CGAL::Epick_d< CGAL::Dimension_tag<3> >;
//using Point = Kernel::Point_d;
//using Vector_of_points = std::vector<Point>;
//typedef CGAL::Exact_predicates_inexact_constructions_kernel Gt;
//typedef Gt::Point_3                                  Ppoint;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Regular_triangulation_vertex_base_3<K> Vbb;
typedef CGAL::Alpha_shape_vertex_base_3<K,Vbb>         Vb;
typedef CGAL::Alpha_shape_cell_base_3<K>           Fb;
typedef CGAL::Triangulation_data_structure_3<Vb,Fb> Tds;
typedef CGAL::Regular_triangulation_3<K,Tds>       Triangulation_3;
typedef CGAL::Alpha_shape_3<Triangulation_3>        Alpha_shape_3;
typedef Alpha_shape_3::Cell_handle          Cell_handle;
typedef Alpha_shape_3::Vertex_handle        Vertex_handle;
typedef Alpha_shape_3::Facet                Facet;
typedef Alpha_shape_3::Edge                 Edge;
typedef K::Weighted_point_3                 Weighted_point;
typedef K::Point_3                          Bare_point;

using std::set;
using namespace std;
class RandomHomology {
public:
    int dim;
    MortonCode *mc;
    ANNkd_tree *kd_tree;
    set<int>removed_ids;
    vector<vector<int>> indices;
    vector<vector<float>> initial_points;
    RandomHomology(vector<vector<float>> &points,
                   vector<float> &min_bounds,
                   vector<float> &max_bounds, int dim);
    RandomHomology(GIC &g);
    ~RandomHomology() {};
    void run(double alpha);
    void run(double alpha, string input_points_file, vector<Operation*> &c);
    void collapseToClosest(MortonPoint p, vector<Operation*> &collapses);
};

#endif /* RandomHomology_hpp */
