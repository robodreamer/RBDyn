// This file is part of RBDyn.
//
// RBDyn is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RBDyn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with RBDyn.  If not, see <http://www.gnu.org/licenses/>.

// associated header
#include "FK.h"

// includes
#include "Joint.h"
#include "MultiBody.h"
#include "MultiBodyConfig.h"

namespace rbd
{

void forwardKinematics(const MultiBody& mb, MultiBodyConfig& mbc)
{
	const std::vector<Joint>& joints = mb.joints();
	const std::vector<int>& pred = mb.predecessors();
	const std::vector<sva::PTransform>& Xt = mb.transforms();

	for(std::size_t i = 0; i < joints.size(); ++i)
	{
		sva::PTransform X_i = joints[i].pose(mbc.q[i]);
		sva::PTransform X_p_i = X_i*Xt[i];

		if(pred[i] != -1)
			mbc.bodyGlobal[i] = X_p_i*mbc.bodyGlobal[pred[i]];
		else
			mbc.bodyGlobal[i] = X_p_i;
	}
}

} // namespace rbd
