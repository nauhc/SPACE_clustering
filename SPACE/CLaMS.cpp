#include "CLaMS.h"
#include <iomanip>
#include <GLError.h>
#include <constant.h>

GLint offset = 5816;
CLaMS::CLaMS()
    :AbstractData(),m_pVBOPathLine(NULL)
    ,m_pathlineIdMax(0), m_pathlineIdMin(INT_MAX_POSITIVE)
	,m_activePathlineId(offset),m_maxPathlineToShow(100),m_totalCount(0)
{
}

CLaMS::~CLaMS()
{
}

void CLaMS::CreateVBO(){

    if(m_pVBOPathLine)
       m_pVBOPathLine = NULL;

    m_pVBOPathLine = 
        std::shared_ptr<GLVertexBufferObject<vec3f> >
		(new GLVertexBufferObject<vec3f>(GL_LINE_STRIP,GL_STATIC_DRAW,true));


    m_pVBOPathLine->enableVertex(true);
    m_pVBOPathLine->setVertexType(GL_FLOAT);
    m_pVBOPathLine->setVertexComponetSize(3);
    m_pVBOPathLine->setVertexOffsetInBytes(0);
    m_pVBOPathLine->setVertexStrideInBytes(2*sizeof(vec3f));
    m_pVBOPathLine->enableColor(true);
    m_pVBOPathLine->setColorType(GL_FLOAT);
    m_pVBOPathLine->setColorComponentSize(3);
    m_pVBOPathLine->setColorOffsetInBytes(1* sizeof(vec3f));
    m_pVBOPathLine->setColorStrideInBytes(2*sizeof(vec3f));
    /*
    */

    /*
    m_pVBO->addAttribute(m_programId,"time", GL_FLOAT,1, 
                         sizeof(vertexMIPASAttribute), 
                         offsetof(vertexMIPASAttribute, time),
                         true);


    m_pVBO->addAttribute(m_programId,"detection", GL_UNSIGNED_INT, 1, 
                        sizeof(vertexCLaMSAttribute), 
                        offsetof(vertexCLaMSAttribute, detection));
    m_pVBO->addAttribute(m_programId,"seedId", GL_INT,1, 
                         sizeof(vertexCLaMSAttribute), 
                         offsetof(vertexCLaMSAttribute, seed_id) );

    m_pVBOPathLine->addAttribute(m_programId,"in_Position", GL_FLOAT, 3, 
                    sizeof(vertexCLaMSAttribute), 
                    offsetof(vertexCLaMSAttribute, positions.posPlanar));

    m_pVBOPathLine->addAttribute(m_programId,"in_posSpherical", GL_FLOAT, 3, 
                    sizeof(vertexCLaMSAttribute), 
                    offsetof(vertexCLaMSAttribute, positions.posSpherical));

    m_pVBOPathLine->addAttribute(m_programId,"pot_vorticity", GL_FLOAT, 1, \
                    sizeof(vertexCLaMSAttribute),\
                    offsetof(vertexCLaMSAttribute, pot_vorticity));
    */
    /*
    m_pVBOSeeds = 
        std::shared_ptr<GLVertexBufferObject<vertexPosAttribute> >
        (new GLVertexBufferObject<vertexPosAttribute>(GL_POINTS,GL_STATIC_DRAW));

    m_pVBOSeeds->enableVertex(true);
    m_pVBOSeeds->setVertexType(GL_FLOAT);
    m_pVBOSeeds->setVertexComponetSize(3);
    m_pVBOSeeds->setVertexOffsetInBytes(0);
    m_pVBOSeeds->setVertexStrideInBytes(sizeof(vertexPosAttribute));
    m_pVBOSeeds->addAttribute(m_programId,"in_posSpherical", GL_FLOAT, 3, 
                        sizeof(vertexPosAttribute), 
                        offsetof(vertexPosAttribute, posSpherical));
*/
    float R = 1.0f;
    cout << std::setprecision(10) << std::fixed ;
    m_bboxPlanarMode = BBox();
    //Normalization time, ash and SO2
    float max_pot_vort = -FLOAT_MAX, min_pot_vort = FLOAT_MAX;
    
    //compute min-max and bbox of the data domain.
    for (int iVtx=0 ; iVtx < m_databuffer.size(); iVtx++)
    {
        CLaMSAttribute& cur_point = m_databuffer[iVtx];
        m_bboxPlanarMode << vec3f(cur_point.lon, cur_point.lat, cur_point.alt);
        max_pot_vort = max_pot_vort < cur_point.pot_vorticity ? cur_point.pot_vorticity : max_pot_vort;
        min_pot_vort = min_pot_vort > cur_point.pot_vorticity ? cur_point.pot_vorticity : min_pot_vort;
    }
	m_bboxPlanarMode.pMin.setX(-180.0);
	m_bboxPlanarMode.pMax.setX(180.0);//(89.733297729);
    m_bboxPlanarMode.pMin.setY(-90.0);
    m_bboxPlanarMode.pMax.setY(90.0);//(89.733297729);
    cout << "CLaMS bbox planar:" <<m_bboxPlanarMode;

    //normalize the vertex coordinates using the bbox we just build.
    float inv_pot_vort = 1.0f/(max_pot_vort - min_pot_vort);
    vec3f invScaleXYZ = vec3f(2.0f)/m_bboxPlanarMode.MaximumExtentf();
    vec3f center = m_bboxPlanarMode.Center();
	center.setZ(0.0f);
    //Feed VBO
    vertexCLaMSAttribute vtxAttr;
    for (int iVtx=0 ; iVtx < m_databuffer.size(); iVtx++)
    {
        CLaMSAttribute& cur_point = m_databuffer[iVtx];
		double tmp = cur_point.lon;
        //I think the lat and lon of CLaMS is mistakenly swapped in the original data set.
		cur_point.lon = cur_point.lat;
		cur_point.lat = tmp;
        vertexPosAttribute  vtxPosAttrib;
       
        vtxPosAttrib.posPlanar = vec3f(cur_point.lon, cur_point.lat, cur_point.alt);
        vtxPosAttrib.posPlanar = (vtxPosAttrib.posPlanar-center)*invScaleXYZ;//normalize.
        
        float y = (R+vtxAttr.positions.posPlanar.z()) * sin(cur_point.lat*DEG2RAD);
        float x = (R+vtxAttr.positions.posPlanar.z()) * cos(cur_point.lat*DEG2RAD)*sin(cur_point.lon*DEG2RAD);
        float z = (R+vtxAttr.positions.posPlanar.z()) * cos(cur_point.lat*DEG2RAD)*cos(cur_point.lon*DEG2RAD);
        vtxPosAttrib.posSpherical = vec3f(x,y,z);
        
        vtxAttr.positions = vtxPosAttrib;
        vtxAttr.pot_vorticity = (cur_point.pot_vorticity - min_pot_vort) * inv_pot_vort;

        *m_pVBOPathLine << vtxAttr.positions.posSpherical;//comment me to see 3D spherical projection.

//      *m_pVBOPathLine << vtxAttr.positions.posPlanar;//comment me to see 2D projection.
        if (vtxAttr.pot_vorticity > 0.5)
        {//color the line based on the vorticity.
            *m_pVBOPathLine << vec3f(1,0,0);//add color for the current vertex.
        }
        else
        {
            *m_pVBOPathLine << vec3f(0,0,1);//add color for the current vertex.
        }
    }
    
    m_invScale = 1.0f/m_bboxPlanarMode.MaximumExtentf();

    //Create index buffer from m_pathLineConnectivity
    m_ibo = std::shared_ptr<GLIndexBufferObject>
            (new GLIndexBufferObject(GL_LINE_STRIP_ADJACENCY));

    m_ibo->enableRestart(true);
    m_ibo->setRestartIndex(-1);
    m_pathlineStartCountPairs.resize(m_pathLinesConnectivity.size());

    size_t startOffset = 0;
    for (size_t i = 0 ; i < m_pathLinesConnectivity.size() ;i++)
    {
        std::vector<size_t>& curPtIndices = m_pathLinesConnectivity[i].pointIndices;
        size_t ptCount = curPtIndices.size();
        m_pathlineStartCountPairs[i].setX(startOffset);
        m_pathlineStartCountPairs[i].setY(ptCount+1);
        for (size_t j = 0 ; j < ptCount ; j++)
        {
            *m_ibo << curPtIndices[j];
        }
        *m_ibo << -1;
        startOffset += (ptCount+1);//restart index counts.
    }

    m_totalCount=0;
    for (size_t i = 0 ; 
        i < m_maxPathlineToShow 
        && m_activePathlineId+i < m_pathLinesConnectivity.size();
		i++)
    {
        m_totalCount += m_pathlineStartCountPairs[m_activePathlineId+i].y();
    }

    m_activePathlineId = m_pathLinesConnectivity.size()-m_maxPathlineToShow;//offset;
}

void CLaMS::draw()
{
    vec3f center = m_bboxPlanarMode.Center();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_DEPTH_TEST);
   
    glLineWidth(1.0);
    //glPointSize(m_pointSize);
    glColor3fv((float*)m_color);
    //Center the displayed data.
    m_pVBOPathLine->bind();
	//y()=the index of 1st point in the cur_orbit,z()=the count of the points in the cur_orbit
    m_ibo->bind();
    //cout << "m_activePathlineId="<<m_activePathlineId<<endl;
    //cout << "totalCount="<<m_totalCount<<endl;
    m_ibo->draw(m_pathlineStartCountPairs[m_activePathlineId].x()\
                ,m_totalCount);//
		//,m_pathlineStartCountPairs[m_activePathlineId].y());
    m_ibo->unbind();
    m_pVBOPathLine->unbind();

    glPopAttrib();
    glPopMatrix();
}

void CLaMS::load( const string& fileName )
{
    //Read bin file
    //ifstream ifs("volcano_2011_150_pm.vtk.bin", ios::binary);
    cout<<"***Loading CLaMS data*****\n";
    ifstream ifs(fileName, ios::binary);
    size_t count = 0;
    if (!ifs)
    {
        GLError::ErrorMessage("data file not found!\n");
    }
    ifs.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    cout <<"# of data points: "<<count<<endl;
    m_databuffer.resize(count);
    ifs.read(reinterpret_cast<char*>(m_databuffer.data()), sizeof(CLaMSAttribute)*count);

    //lines
    ifs.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    cout << "Read in "<<count<<" CLaMs Lines\n";
    m_pathLinesConnectivity.resize(count);

    for (int i=0 ; i < count ; i++)
    {//for each line read-in
        CLaMSPathLine& pathline = m_pathLinesConnectivity[i];
        //seed id
        ifs.read(reinterpret_cast<char*>(&(pathline.seedId)), sizeof(int));
        //point count
        size_t count=0;
        ifs.read(reinterpret_cast<char*>(&count), sizeof(size_t));
        //point indices
        pathline.pointIndices.resize(count);
        ifs.read(reinterpret_cast<char*>(pathline.pointIndices.data()),
                 sizeof(size_t)*count);
    }

    ifs.close();

    CreateVBO();
}

void CLaMS::setCurActivePathLineId( GLuint n )
{ 
	m_activePathlineId = (GLuint)std::max((int)n, (int)0);
	m_activePathlineId = std::min(m_activePathlineId, 
		(GLint)(m_pathLinesConnectivity.size()-1));
    m_totalCount=0;
    for (size_t i = 0 ; 
         i < m_maxPathlineToShow 
         && m_activePathlineId+i < m_pathLinesConnectivity.size();
         i++)
    {
        m_totalCount += m_pathlineStartCountPairs[m_activePathlineId+i].y();
    }
	cout << "curSelectedPathLine"<<m_activePathlineId
        <<"=(start:" << m_pathlineStartCountPairs[m_activePathlineId].x()
        <<"count:"<< m_totalCount <<endl;
}

void CLaMS::clustering(  ){
	int n_pathln	= m_pathLinesConnectivity.size(); //pathline number
	int n_feature	= 6; //feature numer: pressure, temp, vorticity, (x, y, z)

	QVector<int> ids; 
	ids.resize(n_pathln);
	for(int q = 0; q < ids.size(); ++q){
		ids[q] = m_pathLinesConnectivity[q].seedId;
	}
	QVector<int> results = ids;
	
	int clustermethod = 0; //0 or 1
	int numCluster = 20;
	if(numCluster > ids.size()){
		cout << "error: numCluster greater than pathline number." << endl;
		return;
	}

	const char dist = 'c';		//several choices
	const char method = 'a';	// several choices
	int npass = 100;
	int ifound = 0;
	const int nclusters = numCluster;
	const int transpose = 0;
	double error;

	int nrows = n_pathln;
	int ncols = n_feature;
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

	//set data
	for(size_t a = 0; a < ids.size(); ++a){
		int id = ids[a];

		data[a][0] = 
	}

}