#ifndef __TITAN_RENDERABLE_HH
#define __TITAN_RENDERABLE_HH

#include "TitanPrerequisites.h"
#include "TitanShaderEffect.h"

namespace Titan
{
	class _DllExport Renderable : public GeneralAlloc
	{
	public:
		Renderable(){};

		virtual ~Renderable(){};

		virtual void			getRenderData(RenderData& rd) = 0;

		virtual void			getTransformMat(Matrix4* transMat) = 0;

		virtual RenderData*		getRenderData() = 0;

		virtual ShaderEffectPtr	getShaderEffect() = 0;

		virtual bool			hasShader() = 0;

	protected:
	};
}
#endif