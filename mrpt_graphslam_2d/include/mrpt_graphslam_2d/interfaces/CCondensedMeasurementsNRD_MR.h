/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#ifndef CCONDENSEDMEASUREMENTSNRD_MR_H
#define CCONDENSEDMEASUREMENTSNRD_MR_H

#include <mrpt/utils/COutputLogger.h>
#include <string>

namespace mrpt { namespace graphslam { namespace deciders {

/**\brief Node Registration Decider virtual method.
 *
 * \b Node Registration Decider classes that are to be used in a multi-robot
 * SLAM scheme according to the Condensed Measurements multi-robot strategy by
 * M.T. Lazaro et al. [1] are to inherit from this method.
 *
 *\note Node Registration related classes are suffixed with NRD.
 *
 * \note Multi-robot related classes are suffixed MR (stands for
 * multi-robot).
 *
 * \note For an example of inheriting from this class, see the
 * mrpt::graphslam::deciders::CFixedIntervalsNRD_MR.
 *
 * [1] <a
 * href="http://webdiis.unizar.es/~mtlazaro/papers/Lazaro-IROS13.pdf">Multi-robot
 * SLAM using Condensed Measurements</a> - M.T. Lazaro, L.M. Paz, P. Pinies,
 * J.A. Castellanos, G. Grisetti
 */
template<class GRAPH_t>
class CCondensedMeasurementsNRD_MR :
	public virtual mrpt::utils::COutputLogger
{
public:
	CCondensedMeasurementsNRD_MR ();
	~CCondensedMeasurementsNRD_MR ();

protected:
};

} } } // end of namespaces

#include "CCondensedMeasurementsNRD_MR_impl.h"
#endif /* end of include guard: CCONDENSEDMEASUREMENTSNRD_MR_H */
