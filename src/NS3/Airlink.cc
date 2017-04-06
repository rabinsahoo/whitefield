#define	_AIRLINK_CC_

#include "ns3/core-module.h"
#include "ns3/lr-wpan-module.h"
#include "ns3/mobility-module.h"

#include "Airlink.h"

using namespace ns3;

void Airlink::getAllNodeLocation(void)
{
	NodeContainer const & n = NodeContainer::GetGlobal (); 
	for (NodeContainer::Iterator i = n.Begin (); i != n.End (); ++i) 
	{ 
		Ptr<Node> node = *i; 
		//std::string name = Names::FindName (node); // Assume that nodes are named, remove this line otherwise 
		Ptr<MobilityModel> mob = node->GetObject<MobilityModel> (); 
		if (! mob) continue; // Strange -- node has no mobility model installed. Skip. 

		Vector pos = mob->GetPosition (); 
		std::cout << "Node is at (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n"; 
	} 
}

int Airlink::startNetwork(wf::Config & cfg)
{
	NodeContainer nodes;
	nodes.Create (cfg.getNumberOfNodes());
	INFO << "Creating " << cfg.getNumberOfNodes() << " nodes..\n";
	SeedManager::SetSeed(0xbabe);

	MobilityHelper mobility;
	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
			"MinX", DoubleValue(.0),
			"MinY", DoubleValue(.0),
			"DeltaX", DoubleValue(stod(cfg.get("fieldX"))),
			"DeltaY", DoubleValue(stod(cfg.get("fieldY"))),
			"GridWidth", UintegerValue(stoi(cfg.get("deploymentMode"))),
			"LayoutType", StringValue("RowFirst"));

	mobility.Install (nodes);

	NS_LOG_INFO ("Create channels.");
	LrWpanHelper lrWpanHelper;
	NetDeviceContainer devContainer = lrWpanHelper.Install(nodes);
	lrWpanHelper.AssociateToPan (devContainer, stoi(cfg.get("panID")));

	getAllNodeLocation();
	Simulator::Run ();
	Simulator::Destroy ();
	INFO << "Execution done\n";
	return SUCCESS;
}

Airlink::Airlink(wf::Config & cfg)
{
	startNetwork(cfg);
	INFO << "Airlink started" << endl;
}