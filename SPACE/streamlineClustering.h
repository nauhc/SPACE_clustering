#pragma once

#include <qvector.h>
#include "cluster.h"

struct OneLine{
	int		linesID; //ID
	double	cdist;   // dist to center
};

class streamlineClustering
{
private:
	QVector<int> ids; // = linesID
	QVector<int> results; 
	QVector<OneLine> lineInfo;
	QVector<double> center;
	int clustermethod;
	int numCluster;

public:
	streamlineClustering(void);
	~streamlineClustering(void);

	int 	m_clusteringMode;
	int		m_nosClusters1,m_nosClusters2; // 0: non-init, 1,2,3...etc
	//vector<Vector3>	m_cluster1Color,m_cluster2Color;

	void	setStreamlineIDs();
	void	setClusterNum(int num);
	void    runKMeans(QVector<int> &target,
					  QVector<int> &resultID,
					  int nosCluster,
					  QVector<QVector<double> > &center,
					  int method=0);

	void	doClustering();

};

