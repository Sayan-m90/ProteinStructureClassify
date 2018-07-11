/*****************************************************************************/
"Sibaco" is used for computing persistence of a weighted input point cloud 
/*****************************************************************************/

"Sibaco" is developed by the Jyamiti research group headed by 
Prof. Tamal K. Dey at the Department of Computer Science and Engineering 
of The Ohio State University.

The binaries are distributed for: Ubuntu Linux 64bit; This is the source code in Github

=================================
DESCRIPTION
=================================

The "Sibaco" software can compute computing persistence of an input weighted point cloud.
This software is developed based on the following paper:

	* Paper: T. K. Dey, S. Mandal
	Improved Image Classification using Topological Persistence (accepted at WABI, 2018)

Compile the software in Linux using the script file build.sh as provided. It's Pre-requisites are:
1. Boost(https://www.boost.org/)
2. CGAL(https://www.cgal.org/)
3. ANN (http://www.cs.umd.edu/~mount/ANN/)
For installation in Windows or Mac, install these two dependencies then compile as a project

=================================
USAGE
=================================
-------------------------------------------------------------------------------
./Sibaco -i <input_points_file> -m <max_dim> -s <subsample_raio> -n <nearest_neighbor> [-options]
-------------------------------------------------------------------------------

SimBa Usage:
  -h				Help information;

  -l				License information;

  -i arg			Input file name containing weighted point cloud;

  -m arg			 The maximum dimension the user wants to see in the 
                        	output persistent barcodes (betti no.). (default value: 2);

  -s arg 			The subsample ratio to choose in subsequent collapse 
                        	operations. Chooses every sth datapoint in the Octree 
                        	ordering (default value: 5);

  -n arg 			  The number of nearest neighbours to create the intial 
	                        graph. (default value: 2)

=================================
INPUT PARAMETERS:
=================================

<input_points>       	: input points file in the following format:
				/////////////////
				x_1 x_2 ... x_d w_d # coordinates of the first point followed by its weight
				 ...
				x_1 x_2 ... x_d w_d #coordinates of the last point followed by its weight
				/////////////////
				Example: the following file contains 2 points in R^3
				*****************
				* 1.0 1.0 1.0 5.0	*
				* -2.0 2.0 2.0 7.0	*
				* 3.0 -3.0 3.0 10.0	*
				*****************

=================================
OUTPUT FILES:
=================================

"Sibaco" produces the following output file: 
1) <persistence_result> : the file contains the output persistence.

Each line gives a persistence barcode of the image H(K)--f1--f2--...--fn--> H(L) in the indicated dimension:
	
	dim_p birth_time_1 death_time_1
	dim_p birth_time_2 death_time_2
	...
	dim_p birth_time_k death_time_k	

	Notice:
	If a barcode has infinite persistence then the death_time for this pair is "inf";
	Example: the following is output persistence file for the previous elementary simplicial map example
	*****************************************************************************		
	* 0 0.1 inf
	* 0 0.1 0.2
	* 0 0.1 0.2
	* 1 0.2 0.4
	*****************************************************************************


=================================
EXAMPLE
=================================

A sample input points file "1o9a.pdb_data2" is provided in "PDB-file" folder
which givens 13387 points representing the molecules in the protein structure with ID 1o9a

Run the following command:

Complete command:
	./sibaco -i 1o9a.pdb_data2.txt -n 7 -s 8

Or simply use default parameters value: 
	./sibaco -i 1o9a.pdb_data2.txt


=================================
LEGAL TERMS
=================================

THIS SOFTWARE IS PROVIDED "AS-IS". THERE IS NO WARRANTY OF ANY KIND. 
NEITHER THE AUTHORS NOR THE OHIO STATE UNIVERSITY WILL BE LIABLE FOR 
ANY DAMAGES OF ANY KIND, EVEN IF ADVISED OF SUCH POSSIBILITY.

This software was developed (and is copyrighted by) the Jyamiti group at 
The Ohio State University. Please do not redistribute this software. 
This program is for academic research use only. This software uses the  
Boost library (www.boost.org) and Ann library
(www.cs.umd.edu/~mount/ANN/) which are covered under their own licenses.

 
---------------------------------------------------------------------------

The Boost library's license 
(which applies to the Boost library ONLY and NOT to this program itself) is 
as follows:

LICENSE
---------------------------------------------------------------------------
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
---------------------------------------------------------------------------

ANN library's license
(which applies to the ANN library ONLY and NOT to this program itself) is 
as follows:

LICENSE
---------------------------------------------------------------------------
The ANN Library (all versions) is provided under the terms and
conditions of the GNU Lesser General Public Library, which is stated
below.  It can also be found at:

   http://www.gnu.org/copyleft/lesser.html
---------------------------------------------------------------------------
