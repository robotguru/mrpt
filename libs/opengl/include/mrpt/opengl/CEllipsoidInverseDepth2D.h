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
#ifndef opengl_CEllipsoidInverseDepth2D_H
#define opengl_CEllipsoidInverseDepth2D_H

#include <mrpt/opengl/CGeneralizedEllipsoidTemplate.h>

namespace mrpt
{
	namespace opengl
	{
		// This must be added to any CSerializable derived class:
		DEFINE_SERIALIZABLE_PRE_CUSTOM_BASE_LINKAGE( CEllipsoidInverseDepth2D, CRenderizableDisplayList, OPENGL_IMPEXP )

		/** An especial "ellipsoid" in 3D computed as the uncertainty iso-surfaces of a (inv_range,yaw) variable.
		  *  The parameter space of this ellipsoid comprises these variables (in this order):
		  *   - inv_range: The inverse distance from the sensor to the feature.
		  *   - yaw: Angle for the rotation around +Z ("azimuth").
		  *
		  *  This parameterization is a 2D version of that presented in the paper:
		  *   - Civera, J. and Davison, A.J. and Montiel, J., "Inverse depth parametrization for monocular SLAM", T-RO, 2008.
		  *
		  *  This class expects you to provide a mean vector of length 4 and a 4x4 covariance matrix, set with \a setCovMatrixAndMean().
		  *
		  *  <div align="center">
		  *  <table border="0" cellspan="4" cellspacing="4" style="border-width: 1px; border-style: solid;">
		  *   <tr> <td> mrpt::opengl::CEllipsoidInverseDepth2D </td> <td> \image html preview_CEllipsoidInverseDepth2D.png </td> </tr>
		  *  </table>
		  *  </div>
		  *
		  * \ingroup mrpt_opengl_grp
		  */
		class OPENGL_IMPEXP CEllipsoidInverseDepth2D : public CGeneralizedEllipsoidTemplate<2>
		{
			typedef CGeneralizedEllipsoidTemplate<2> BASE;
			DEFINE_SERIALIZABLE( CEllipsoidInverseDepth2D )

		public:
			/** The maximum range to be used as a correction when a point of the ellipsoid falls in the negative ranges (default: 1e6) */
			void setUnderflowMaxRange(const double maxRange) { m_underflowMaxRange = maxRange; }
			double getUnderflowMaxRange() const { return m_underflowMaxRange; }


		protected:
			/** To be implemented by derived classes: maps, using some arbitrary space transformation, a list of points 
			  *  defining an ellipsoid in parameter space into their corresponding points in 2D/3D space.
			  */
			virtual void transformFromParameterSpace(
				const std::vector<BASE::array_parameter_t> &in_pts,
				std::vector<BASE::array_point_t> & out_pts) const;
		private:
			double m_underflowMaxRange; 

			/** Constructor
			  */
			CEllipsoidInverseDepth2D() : m_underflowMaxRange(1e6)
			{
			}
			/** Private, virtual destructor: only can be deleted from smart pointers */
			virtual ~CEllipsoidInverseDepth2D() { }
		};

	} // end namespace

} // End of namespace

#endif