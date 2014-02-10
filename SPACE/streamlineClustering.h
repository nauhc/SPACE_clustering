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
	int nrows; // pathline dimension 
	int ncols; // feature dimension
	int		*clusterid;
	double	**data;
	double	**cdata;
	int		**mask;
	double	*weight;

	QVector<int> target; // = linesID
	QVector<int> results; 
	QVector<OneLine> lineInfo;
	QVector<double> center;
	int clustermethod;
	int numCluster;

public:
	streamlineClustering(void);
	~streamlineClustering(void);

	void	setStreamlineIDs();
	void	setData(int pathlineDim, int featDim);
	void	setClusterNum(int num);
	void    runKMeans(QVector<int> &target,
					  QVector<int> &resultID,
					  int nosCluster,
					  QVector<QVector<double> > &center,
					  int method=0);

	void	doClustering();

};

