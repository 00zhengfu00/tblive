//------------------------------------------------------------------------------
//
//    ��Ȩ����(C) ����Ͱͣ��й������缼�����޹�˾ ��������Ȩ��
//
//    ������:   ����
//    ��������: 2011-11-07
//    ��������: ��Ϣ���ĺ��Ķ���
//
//
//------------------------------------------------------------------------------

#ifndef __PRGMESSAGECENTER_H_D8247C0A_B654_446B_ACD2_370E0B438C4E_INCLUDED__
#define __PRGMESSAGECENTER_H_D8247C0A_B654_446B_ACD2_370E0B438C4E_INCLUDED__

#include <core/IPrgMC.h>
#include <base/memory/ref_counted.h>
#include <base/memory/ref_ptrcounted.h>
#include "base/synchronization/lock.h"
#include "PrgMCRegistration.h"
#include "PrgMCAsyncProcessor.h"
#include "PrgMCSyncProcessor.h"

class CPrgMessageCenter : public base::RefPtrCounted<prg::IPrgMC, base::ThreadSafeRefPolicy>
{
public:
    CPrgMessageCenter();
    virtual ~CPrgMessageCenter();

    virtual HRESULT Init(int nAsyncMaxThread = 1) OVERRIDE;

    virtual HRESULT UnInit() OVERRIDE;

    virtual HRESULT RegisterMessage(const std::wstring& strMsg, IPrgMsgHandler *pHandler, prg::REGISTERTYPE type) OVERRIDE;

    virtual HRESULT UnRegisterMessage(const std::wstring& strMsg, IPrgMsgHandler *pHandler) OVERRIDE;

    virtual HRESULT SendMessage(const std::wstring& strMsg, prg::IXParam *pParam, prg::IXParam *pSender) OVERRIDE;

    virtual HRESULT PostMessage(const std::wstring& strMsg, prg::IXParam *pParam, prg::IXParam *pSender, prg::ASYNCPRIORITYTYPE type) OVERRIDE;
    
    virtual HRESULT RegisterGlobalFilter(IPrgMsgHandler *pHandler) OVERRIDE;

    virtual HRESULT UnRegisterGlobalFilter(IPrgMsgHandler *pHandler) OVERRIDE;

    virtual HRESULT ClearPostMessages() OVERRIDE;

private:
    scoped_refptr<CPrgMCRegistration> m_spRegistration;
    scoped_refptr<CPrgMCAsyncProcessor> m_spAsyncProcessor;
    scoped_ptr<CPrgMCSyncProcessor> m_spSyncProcessor;

    bool m_bInited;
    base::Lock m_lock;
};


#endif // #ifndef __PRGMESSAGECENTER_H_D8247C0A_B654_446B_ACD2_370E0B438C4E_INCLUDED__
