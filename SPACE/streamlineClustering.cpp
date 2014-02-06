#include "streamlineClustering.h"


streamlineClustering::streamlineClustering(void){
	// --- initialize lineInfo


	ids.resize(lineInfo.size());
	for(int q=0;q<ids.size();++q)
		ids[q] = lineInfo[q].linesID;

	QVector<int> results = ids;
	clustermethod = 0;
	numCluster = 10;
}


streamlineClustering::~streamlineClustering(void){
}

void streamlineClustering::doClustering(){

}

void streamlineClustering::runKMeans(QVector<int> &target,
									QVector<int> &resultID,
									int nosCluster,
									QVector<QVector<double> > &center,
									int method=0){
	int nrows = target.size();
	int ncols = 9; // number of features, starting (x,y,z), middle, ending

		if(clustermethod == 1)
		ncols = 2; // // entL, entA

	center.resize(nrows);
	for(int a=0;a<nrows;++a)
		center[a].resize(ncols);

	const char dist = 'c';
	const char method = 'a';
	int npass = 100;
	int ifound = 0;
	const int nclusters = nosCluster;
	const int transpose = 0;
	double error;

	int		*clusterid = new int[nrows];
	double	**data = new double*[nrows];
	double	**cdata = new double*[nrows];
	int		**mask = new int*[nrows];
	double	*weight = new double[ncols];

	for(int w=0;w<nrows;++w){
		data[w] = new double[ncols];
		mask[w] = new int[ncols];
		cdata[w] = new double[ncols];
	}
	for(int q=0;q<ncols;q++) weight[q] = 1.0;

	for(size_t a=0;a<target.size();++a){
		int id = target[a];

		if(clustermethod == 0){
			int lastone = m_streamLines[id]->m_pt.size()-1;
			int midone = m_streamLines[id]->m_pt.size()/2;
			float bx = m_streamLines[id]->m_pt[0].x();
			float by = m_streamLines[id]->m_pt[0].y();
			float bz = m_streamLines[id]->m_pt[0].z();
			float ex = m_streamLines[id]->m_pt[lastone].x();
			float ey = m_streamLines[id]->m_pt[lastone].y();
			float ez = m_streamLines[id]->m_pt[lastone].z();

			data[a][0] = bx;	data[a][1] = by;	data[a][2] = bz;
			data[a][3] = m_streamLines[id]->m_pt[midone].x();
			data[a][4] = m_streamLines[id]->m_pt[midone].y();
			data[a][5] = m_streamLines[id]->m_pt[midone].z();
			data[a][6] = ex;	data[a][7] = ey;	data[a][8] = ez;
		}
		else if(clustermethod == 1){
			data[a][0] = m_streamLines[id]->m_entropyL;
			data[a][1] = m_streamLines[id]->m_entropyA;
		}

		for(int f=0;f<ncols;++f)
			mask[a][f] = 1;
	//	mask[a][1] = 1;
	//	mask[a][2] = 1;
	}

	kcluster(nclusters,nrows,ncols,data,mask,weight,transpose,npass,method,dist,
			 clusterid,&error,&ifound,
			 cdata);

	// print cdata
	for(int w=0;w<nclusters;++w){
		qDebug("cluster %d:",w);

		char buf[1000] = {0};

		for(int r=0;r<ncols;++r){
			double aaa = cdata[w][r];
			center[w][r] = aaa;

			char localbuf[200] = {0};
			sprintf(localbuf,"%f,",aaa);
			strcat(buf,localbuf);
		}
		qDebug(buf);
		//printf("\n");
	}

	resultID.resize(target.size());
	for(int e=0;e<target.size();++e){
		resultID[e] = clusterid[e];
		fprintf(stderr,"%d,",clusterid[e]);
	}
	// calculate within dist
	double sdist = 0.0;
	int nositem = 0;
	for(int w=0;w<nclusters;++w){
		for(int e=0;e<target.size();++e){
			if(w == resultID[e]){
				nositem++;
				for(int r=0;r<ncols;++r){
					double a1 = center[w][r] - data[e][r];
					sdist += (a1 * a1);
				}
			}
		}
	}
	sdist /= nclusters;
		// calculate between dist
	double bdist = 0.0;
	for(int w=0;w<nclusters;++w){
		for(int s=0;s<nclusters;++s){
			for(int r=0;r<ncols;++r){
				double aaa = cdata[w][r] - cdata[s][r];
				bdist += (aaa*aaa);
			}
		}
	}
	bdist /= nclusters;

	qDebug("");
	qDebug("within:%f",sdist);
	qDebug("between:%f",bdist);
	qDebug("ratio:%f",sdist/bdist);

	//
	delete [] clusterid;
	delete [] weight;
	for(int x=0;x<nrows;++x){
		delete [] data[x];
		delete [] mask[x];
	}
	delete [] data;
	delete [] mask;
}