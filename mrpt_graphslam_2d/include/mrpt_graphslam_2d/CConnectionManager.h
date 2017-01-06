#ifndef CCONNECTIONMANAGER_H
#define CCONNECTIONMANAGER_H

#include <ros/ros.h>
#include <multimaster_msgs_fkie/DiscoverMasters.h>
#include <mrpt_msgs/GraphSlamAgent.h>
#include <mrpt_msgs/GraphSlamAgents.h>
#include <mrpt_bridge/mrpt_bridge.h>

#include <mrpt/utils/COutputLogger.h>
#include <mrpt/system/datetime.h>
#include <mrpt/system/string_utils.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <cstdlib>

namespace mrpt { namespace graphslam { namespace detail {

/**\brief Class responsible of handling the network communication between SLAM
 * agents in the Multi-Robot Condensed Measurements graphSLAM algorithm.
 */
class CConnectionManager
{
public:
	//typedef std::vector<mrpt_msgs::GraphSlamAgent>::iterator agents_it;
	//typedef std::vector<mrpt_msgs::GraphSlamAgent>::const_iterator agents_cit;
	typedef mrpt_msgs::GraphSlamAgents::_list_type::iterator agents_it;
	typedef mrpt_msgs::GraphSlamAgents::_list_type::const_iterator agents_cit;

	/**\brief Constructor */
	CConnectionManager(
			mrpt::utils::COutputLogger* logger,
			ros::NodeHandle* nh_in);
	/**\brief Destructor */
	~CConnectionManager();
	/**\brief Fill the given vector with the SLAM Agents that the current manager
	 * can see and communicate with
	 *
	 * \sa updateNearbySlamAgents
	 */
	void getNearbySlamAgents(mrpt_msgs::GraphSlamAgents* agents_vec);
	/**\brief Read-only method for accessing list of nearby agents
	 */
	const mrpt_msgs::GraphSlamAgents&  getNearbySlamAgents();

	/**\brief Wrapper method around the private setup* class methods.
	 *
	 * Handy for setting up publishers, subscribers, services, TF-related stuff
	 * all at once from the user application
	 *
	 */
	void setupComm();

private:
	/**\brief Update the internal list of nearby SLAM agents
	 *
	 * \sa getNearbySlamAgents
	 */
	void updateNearbySlamAgents();
	/**\name setup* ROS-related methods
	 *\brief Methods for setting up topic subscribers, publishers, and
	 * corresponding services
	 *
	 * \sa setupComm
	 */
	/**\{*/
	void setupSubs();
	void setupPubs();
	void setupSrvs();
	/**\}*/


	/**\brief TSlamAgent ==> ROSMaster. */
	static void convert(
			const multimaster_msgs_fkie::ROSMaster& ros_master,
			mrpt_msgs::GraphSlamAgent* slam_agent);
	/**\brief ROSMaster ==> mrpt_msgs::GraphSlamAgent */
	static void convert(
			const mrpt_msgs::GraphSlamAgent& slam_agent,
			multimaster_msgs_fkie::ROSMaster* ros_master);
	/**\brief Remove http:// prefix and port suffix from the string and return result
	 *
	 * \param[out] agent_port Port that the agent is running on. Extracted from
	 * the overall string
	 */
	static std::string extractHostnameOrIP(const std::string& str,
			unsigned short* agent_port=NULL);

	/**\brief Pointer to the logging instance */
	mrpt::utils::COutputLogger* m_logger;
	/**\brief Pointer to the Ros NodeHanle instance */
	ros::NodeHandle* m_nh;

	ros::ServiceClient m_DiscoverMasters_client;
	/**\brief List of slam agents in the current agent's neighborhood */
	mrpt_msgs::GraphSlamAgents m_nearby_slam_agents;

	bool has_setup_comm;


};

} } } // end of namespaces

/**\brief ROSMaster instances are considered the same if the "uri" field is the
 * same
 */
/**\{*/
bool operator==(const multimaster_msgs_fkie::ROSMaster& master1,
		const multimaster_msgs_fkie::ROSMaster& master2);
bool operator!=(const multimaster_msgs_fkie::ROSMaster& master1,
		const multimaster_msgs_fkie::ROSMaster& master2);
/**\{*/

/**\brief GraphSlamAgent instances are considered the same if the "agent_ID" field is the
 * same
 */
/**\{*/
bool operator==(const mrpt_msgs::GraphSlamAgent& agent1,
		const mrpt_msgs::GraphSlamAgent& agent2);

bool operator!=(const mrpt_msgs::GraphSlamAgent& agent1,
		const mrpt_msgs::GraphSlamAgent& agent2);
/**\}*/

#endif /* end of include guard: CCONNECTIONMANAGER_H */
