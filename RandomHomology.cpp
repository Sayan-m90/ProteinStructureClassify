//
//  RandomHomology.cpp
//  BitTests
//
//  Created by Bill Varcho on 2/24/16.
//  Copyright © 2016 Bill Varcho. All rights reserved.
//

#include "RandomHomology.hpp"

RandomHomology::RandomHomology(vector<vector<float>> &points,
                               vector<float> &min_bounds,
                               vector<float> &max_bounds, int _dim) {
    dim = _dim;
    initial_points = points;
    mc = new MortonCode(points, min_bounds, max_bounds);
    kd_tree = Utilities::ConstructKDTree(points, dim);
}

RandomHomology::RandomHomology(GIC &g) {
    dim = g.dim;
    initial_points = g.pts;
    indices = g.indices;
    mc = new MortonCode(g);
    kd_tree = Utilities::ConstructKDTree(initial_points, dim);
}

// exponential backoff on kdtree
void RandomHomology::collapseToClosest(MortonPoint p,
                                       vector<Operation*> &collapses) {
    removed_ids.insert(p.p_id);

    bool neighbor_found = false;
    int current_index = 0;
    int i = 0;
    while (!neighbor_found) {

        // DO ann Query here
        ANNpoint query_point;
        ANNidxArray nn_ids;
        ANNdistArray dists;
        int k = min((int) pow(2, i), (int)initial_points.size());
        double eps = .01;
        query_point = annAllocPt(dim, 0.);
        nn_ids = new ANNidx[k];
        dists = new ANNdist[k];

        for (int d = 0; d < dim; d++) {
            query_point[d] = p.point[d];
        }
        
        kd_tree->annkSearch(query_point,
                            k,
                            nn_ids,
                            dists,
                            eps);

        int check_cout = ceil(pow(2, i-1));
        // check for first point remaining
        for (int j = 0; j < check_cout; j++) {
            set<int>::iterator it;
            it = removed_ids.find(nn_ids[current_index]);
            // id hasn't been removed,so collapse to it
            if (it == removed_ids.end()) {
                //  This details the collapses
                Collapse *c = new Collapse(p.p_id, nn_ids[current_index]);
                collapses.push_back(c);
                j = check_cout;
                neighbor_found = true;
            }
            current_index += 1;
        }
        i += 1;
    }
}

void RandomHomology::run(double alpha, string input_points_file, vector<Operation*> &collapses) {
    

    list<Weighted_point> lwp;
    set<tuple<int,int>> edge_list;

    set<tuple<int,int,int>> triangle_list;

    //input : a small molecule
    Bare_point p;
    int count = -1;
    double alpha_square_max_value {std::numeric_limits<double>::infinity()};
    double last_alpha = 0;
    ifstream is(input_points_file);
    int vcount = 0;
    Timestamp *t = new Timestamp(count+1);
    collapses.push_back(t);
    float smwt = 0;
    while(is >> p)
    {
        float wt;         is>>wt;
        if(wt>smwt)
        	smwt = wt;
        vector<int> simp;
        simp.push_back(vcount+1);
        Insert *s = new Insert(simp);
        collapses.push_back(s);
        vcount ++;
        // t = new Timestamp(count+1);
        // cout<<p<<" "<<wt<<endl;
        lwp.push_back(Weighted_point(p, wt));
        
    }
    count ++;
    t = new Timestamp(count+1);
    collapses.push_back(t);

    Alpha_shape_3  as(lwp.begin(), lwp.end(), smwt, Alpha_shape_3::GENERAL);
    // Gudhi::alpha_complex::Alpha_complex<Kernel> alpha_complex_from_points(points);
    // Gudhi::Simplex_tree<> simplex;
    // initial inserts


    // list<Cell_handle> cells;
    list<Facet>       facets;
    list<Edge>        edges;
    // as.get_alpha_shape_cells(back_inserter(cells),
               // Alpha_shape_3::INTERIOR);
    as.get_alpha_shape_facets(back_inserter(facets),
                Alpha_shape_3::REGULAR);
    // as.get_alpha_shape_facets(back_inserter(facets),
                // Alpha_shape_3::SINGULAR);
    as.get_alpha_shape_facets(back_inserter(facets),
                Alpha_shape_3::SINGULAR);
    as.get_alpha_shape_edges(back_inserter(edges),
               Alpha_shape_3::SINGULAR);
    // cout << " The 0-shape has : " << endl;
    // cout << cells.size() << " interior tetrahedra" << endl;
    cout << facets.size() << " boundary facets" << endl;
    cout << edges.size()  << " singular edges" << endl;
    if(facets.size()>180000)
    {
    	cout<<"Too many. Exit";
    	exit(0);
    }


    for(list<Edge>::const_iterator iterator = edges.begin(); iterator !=edges.end(); ++iterator )
      edge_list.insert( tuple<int,int>(iterator->second,iterator->third) );

    for(list<Facet>::const_iterator iterator = facets.begin(); iterator != facets.end(); ++iterator ){
        vector<int> a ;
        for(int k=1;k<=3;k++)
         {
            list<Weighted_point>::iterator findIter = find(lwp.begin(),lwp.end(),iterator->first->vertex((iterator->second+k)%4)->point());
            a.push_back(distance(lwp.begin(),findIter));
         }
        
        sort(a.begin(),a.end());

        triangle_list.insert(tuple<int,int,int>(a.at(0),a.at(1),a.at(2)));// = distance(lwp.begin(),findIter);
        edge_list.insert(tuple<int,int>(a.at(0),a.at(1)));
        edge_list.insert(tuple<int,int>(a.at(1),a.at(2)));
        edge_list.insert(tuple<int,int>(a.at(0),a.at(2)));

     	  }

	count ++;
    t = new Timestamp(count+1);
    collapses.push_back(t);


    for ( const tuple<int,int>& iter : edge_list)    {
        vector<int> simp;
        simp.push_back(get<0>(iter));
        simp.push_back(get<1>(iter));
        Insert *s = new Insert(simp);
        collapses.push_back(s);
        // cout<<"i "<<iter.get<0>()<<" "<<iter.get<1>()<<" "<<iter.get<2>()<<endl;

    }

    count ++;
    t = new Timestamp(count+1);
    collapses.push_back(t);


    for ( const tuple<int,int,int>& iter : triangle_list)    {
        vector<int> simp;
        simp.push_back(get<0>(iter));
        simp.push_back(get<1>(iter));
        simp.push_back(get<2>(iter));
        Insert *s = new Insert(simp);
        collapses.push_back(s);
        // cout<<"i "<<iter.get<0>()<<" "<<iter.get<1>()<<" "<<iter.get<2>()<<endl;

    }

    int compcount = 0;
    while (mc->size() > 1) {
        // this is for every iteration
        int s = mc->size();
        compcount ++;
        // create another queue
        vector<MortonPoint> keep_pts;
        vector<MortonPoint> remove_pts;
        for (int i = 0; i < s; i++) {
            MortonPoint n = mc->nextPoint();

            //int precision = (int)(alpha*100);
            //cout<<"mc.size: "<<mc->size()<<"precision: "<<precision;
            //getchar();
            // TODO(me): modify this to respect input parameter alpha
            if (i%((int)alpha) != 0) { //  accounting for precision.  it is rejecting every precision th point. higher alpha -> accepts less.. courses scale
                keep_pts.push_back(n);
            } else {
                remove_pts.push_back(n);
            }
        }
        
        for (MortonPoint p : remove_pts) {
            collapseToClosest(p, collapses);
        }
        
        mc->setPoints(keep_pts);
        count += 1;
        Timestamp *t = new Timestamp(count + 1);
        collapses.push_back(t);
        //cout << "# " << count + 1 << endl;
    }
    // cout<< "compcount: "<<compcount <<endl;
}
