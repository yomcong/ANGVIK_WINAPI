//#include "KongAmmoManager.h"
//#include "KongAmmo.h"
//#include "Player.h"
//
//HRESULT KongAmmoManager::Init()
//{
//	vecKongAmmos.resize(kongAmmoMaxCount);
//
//	for (int i = 0; i < kongAmmoMaxCount; ++i)
//	{
//		vecKongAmmos[i] = new KongAmmo;
//		vecKongAmmos[i]->Init();
//	}
//
//	return S_OK;
//}
//
//void KongAmmoManager::Update()
//{
//	for (int i = 0; i < kongAmmoMaxCount; ++i)
//	{
//		vecKongAmmos[i]->Update();
//	}
//}
//
//void KongAmmoManager::Render(HDC hdc)
//{
//	for (int i = 0; i < kongAmmoMaxCount; ++i)
//	{
//		vecKongAmmos[i]->Render(hdc);
//	}
//}
//
//void KongAmmoManager::Release()
//{
//	for (int i = 0; i < kongAmmoMaxCount; ++i)
//	{
//		SAFE_RELEASE(vecKongAmmos[i]);
//	}
//	vecKongAmmos.clear();
//}
//
//void KongAmmoManager::Fire(POINTFLOAT pos, float angle, int dir)
//{
//	for (int i = 0; i < kongAmmoMaxCount; ++i)
//	{
//		// 리사이클 
//		if (vecKongAmmos[i]->GetIsAlive())
//		{
//			continue;
//		}
//
//		vecKongAmmos[i]->IsFire(pos, angle, dir);
//		break;
//	}
//}
