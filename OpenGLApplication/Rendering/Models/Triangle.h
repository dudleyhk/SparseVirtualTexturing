/*



*/
#pragma once
#include "Model.h"


namespace Rendering
{
	namespace Models
	{
		class Triangle : public Models::Model
		{
		public:
			Triangle();
			~Triangle();

			void Create();
			virtual void Update() override final;
			virtual void Draw() override final;
		};
	}
}