#ifndef __TITAN_BASE_TERRAIN__HH
#define __TITAN_BASE_TERRAIN__HH

#include "TiPrerequisites.h"
#include "TiTexture.h"
#include "TitanAABB.h"
#include "TiVector3.h"
#include "TiVertexBuffer.h"
#include "TiIndexBuffer.h"
#include "TiMaterial.h"

namespace Titan
{
	class _DllExport BaseTerrain : public GeneralAlloc
	{
	public:
		struct LocalVertex
		{
			Vector2		xzPos;
			Vector2		localUV;
		};

		struct SectorVertex
		{
			float	height;
			Vector3	normal;
		};

		struct elevationData
		{
			float	minElevation;
			float	maxElevation;
			float	minNormalZ;
			float	maxNormalZ;
			float	strength;
		};

		typedef vector<elevationData>::type elevationDataVec;


	public:
		BaseTerrain();

		virtual ~BaseTerrain();

		virtual void	create(SceneNode* rootNode, TexturePtr heightMap, const AABB& worldBound, uint8 shift = 3);

		virtual void	destroy();

		VertexDeclaration*	getVertexDecl() const { return mVertexDecl; }

		VertexBufferPtr	getHorzVertexData() const { return mHorzVertexData; }

		IndexBufferPtr	getSharedIndexData() const { return mIndexData; }

		float readWorldHeight(uint16 mapX, uint16 mapZ) const;

		float readWorldHeight(uint16 mapIndex) const;

		const Vector3& readWorldNormal(uint16 mapX, uint16 mapZ) const;

		float calcMapHeight(float mapX, float mapY)const;

		void calcMapNormal(Vector3& normal, float mapX, float mapZ)const;

		const Vector2& getSectorSize() const { return mSectorSize;}

		const AABB& getWorldBound() const { return mWorldBound; }

		uint8 getSectorShift() const { return mSectorShift; }

		float computeErrorMetricOfGrid(
			uint16 xVerts,	// width of grid
			uint16 zVerts,	// height of grid
			uint16 xStep,	// horz vertex count per cell
			uint16 zStep,	// vert vertex count per cell
			uint16 xOffset,	// starting index X
			uint16 zOffset);// starting index Z

		float getLodErrorScale() const { return mLodScale;}

		float getRatioLimit() const { return mRatioLimit; }

		void setTessellationParams(float lodScale, float ratioLimit){ mLodScale = lodScale; mRatioLimit = ratioLimit;}

		uint8	getSectorVertex() const { return mSectorVerts; }

		const MaterialPtr&	getMaterial() const;

		void	setMaterial(const String&  name);

		void	genBlendImage(Image& img, const elevationDataVec& elevDataVec);

		uint16	getSectorCountX() const { return mSectorCountX;}

		uint16	getSectorCountZ() const { return mSectorCountZ; }

		
	protected:
		void			_buildHeightAndNormalTables(TexturePtr heightMap);


		virtual void	_buildHorzVertexData();

		virtual void	_buildVertexDecl();

		virtual void	_buildIndexData();

		virtual void	_createTerrainSections();

		virtual void	_setupTerrainMaterial();

	protected:
		BaseTerrainSection**		mSectorArray;
		SceneNode*				mRootNode;
		MaterialPtr				mMaterial;

		float*					mHeightTable;
		Vector3*				mNormalTable;

		VertexBufferPtr	mHorzVertexData;
		VertexDeclaration*		mVertexDecl;
		IndexBufferPtr	mIndexData;

		AABB			mWorldBound;
		
		Vector3			mWorldSize;
		Vector3			mMapScale;
		Vector2			mSectorSize;
		float			mLodScale;
		float			mRatioLimit;
		uint16			mTableWidth;
		uint16			mTableHeight;
		uint16			mSectorCountX;
		uint16			mSectorCountZ;
		uint8			mSectorShift;
		uint8			mSectorUnits;
		uint8			mSectorVerts;
	};
}


#endif