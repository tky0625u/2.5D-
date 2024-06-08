#include "GimmickBase.h"

void GimmickBase::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);  //モデル描画
}

void GimmickBase::DrawLit()
{
	Draw();
}

void GimmickBase::GenerateDepthMapFromLight()
{
	Draw();
}
