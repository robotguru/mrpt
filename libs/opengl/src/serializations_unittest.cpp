/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                       http://www.mrpt.org/                                |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */


#include <mrpt/opengl.h>
#include <mrpt/base.h>
#include <gtest/gtest.h>

using namespace mrpt;
using namespace mrpt::opengl;
using namespace mrpt::utils;
using namespace std;

// Defined in run_unittests.cpp
namespace mrpt { namespace utils {
	extern std::string MRPT_GLOBAL_UNITTEST_SRC_DIR;
  }
}


// Create a set of classes, then serialize and deserialize to test possible bugs:
TEST(SerializeTestOpenGL, WriteReadToMem)
{
	const mrpt::utils::TRuntimeClassId* lstClasses[] = {
		CLASS_ID( C3DSScene ), 
		CLASS_ID( CAxis ), 
		CLASS_ID( CBox ), 
		CLASS_ID( CDisk ), 
		CLASS_ID( CGridPlaneXY ), 
		CLASS_ID( CMesh ), 
		CLASS_ID( COpenGLViewport ), 
		CLASS_ID( CPointCloud ), 
		CLASS_ID( CPointCloudColoured ), 
		CLASS_ID( CSetOfLines ), 
		CLASS_ID( CSetOfTriangles ), 
		CLASS_ID( CSphere ), 
		CLASS_ID( CCylinder ), 
		CLASS_ID( CGeneralizedCylinder ), 
		CLASS_ID( CPolyhedron ), 
		CLASS_ID( CTexturedPlane ), 
		CLASS_ID( CArrow ), 
		CLASS_ID( CCamera ), 
		CLASS_ID( CEllipsoid  ), 
		CLASS_ID( CGridPlaneXZ ), 
		CLASS_ID( COpenGLScene ), 
		CLASS_ID( CSetOfObjects ), 
		CLASS_ID( CSimpleLine ), 
		CLASS_ID( CText ), 
		CLASS_ID( CText3D ),
		CLASS_ID( CEllipsoidInverseDepth2D ),
		CLASS_ID( CEllipsoidInverseDepth3D ),
		CLASS_ID( CEllipsoidRangeBearing2D )
		};

	for (size_t i=0;i<sizeof(lstClasses)/sizeof(lstClasses[0]);i++)
	{
		try
		{
			CMemoryStream  buf;
			{
				CSerializable* o = static_cast<CSerializable*>(lstClasses[i]->createObject());
				buf << *o;
				delete o;
			}

			CSerializablePtr recons;
			buf.Seek(0);
			buf >> recons;
		}
		catch(std::exception &e)
		{
			GTEST_FAIL() <<
				"Exception during serialization test for class '"<< lstClasses[i]->className <<"':\n" << e.what() << endl;
		}
	}
}

