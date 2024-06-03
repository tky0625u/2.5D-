#include "Ground.h"

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);  //モデル描画
}

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Ground/Terrain.gltf");  //モデル読み込み
}
