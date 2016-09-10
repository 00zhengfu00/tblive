//------------------------------------------------------------------------------
//
//    ��Ȩ����(C) ����Ͱͣ��й������缼�����޹�˾ ��������Ȩ��
//
//    ������:   ����
//    ��������: 2011-11-08
//    ��������: ͬ����Ϣ������
//
//
//------------------------------------------------------------------------------

#ifndef __PRGMCSYNCPROCESSOR_H_E7249C8B_3E41_4F59_8846_81E4C88EC9DC_INCLUDED__
#define __PRGMCSYNCPROCESSOR_H_E7249C8B_3E41_4F59_8846_81E4C88EC9DC_INCLUDED__


#include "base/synchronization/lock.h"
#include "base/synchronization/condition_variable.h"

#include <base/memory/ref_counted.h>
#include <base/xparam/IXParam.h>
#include "PrgMCProcessor.h"

class CPrgMCSyncProcessor:public CPrgMCProcessor
{
public:
    CPrgMCSyncProcessor():m_bInited(false), m_lSyncProcessCount(0), m_conditionProcessCount(&m_lock)
    {
    }

    virtual ~CPrgMCSyncProcessor()
    {
    }

    virtual HRESULT Init(scoped_refptr<CPrgMCRegistration> spRegistration, int nFlag) OVERRIDE;
    virtual HRESULT UnInit() OVERRIDE;
    virtual HRESULT Process(const std::wstring& strMsg, prg::IXParam *pParam, prg::IXParam *pSender, int nFlag) OVERRIDE;

private:
    base::Lock m_lock;
    bool m_bInited;
    long m_lSyncProcessCount;
    base::ConditionVariable m_conditionProcessCount;
};


#endif // #ifndef __PRGMCSYNCPROCESSOR_H_E7249C8B_3E41_4F59_8846_81E4C88EC9DC_INCLUDED__
