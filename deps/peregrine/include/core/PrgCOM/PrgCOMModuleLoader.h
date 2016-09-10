//------------------------------------------------------------------------------
//
//    ��Ȩ����(C) ����Ͱͣ��й������缼�����޹�˾ ��������Ȩ��
//
//    ������:   ����
//    ��������: 2015-02-03
//    ��������: PrgCOM��ģ�������
//
//
//------------------------------------------------------------------------------

#ifndef __PrgCOMModuleLoader_H_1664FAA8_8E1F_4AEE_9E6B_63562BDAE418_INCLUDED__
#define __PrgCOMModuleLoader_H_1664FAA8_8E1F_4AEE_9E6B_63562BDAE418_INCLUDED__

#include "map"
#include "list"
#include "base/synchronization/lock.h"
#include "base/native_library.h"
#include "core/IPrgCOMFactory.h"
#include "base/memory/ref_counted.h"
#include "base/files/file_path.h"

class CPrgCOMModuleLoader
{
public:
    CPrgCOMModuleLoader();
    ~CPrgCOMModuleLoader();

    HRESULT Init(const base::FilePath &path);
    HRESULT Uninit();

    HRESULT GetPrgCOMFactory(const base::FilePath &dllpath, prg::IPrgCOMFactory **ppFactory);
    
private:
    class ModuleHandle : public base::RefCountedThreadSafe<ModuleHandle>
    {
	public:
        ModuleHandle():library(NULL), pFactory(NULL)
        {

        }

        base::NativeLibrary library;
        prg::IPrgCOMFactory *pFactory;
        base::Lock lock;
        
    private:
        friend class base::RefCountedThreadSafe<ModuleHandle>;
        ~ModuleHandle()
        {
        }
    };

	scoped_refptr<ModuleHandle> GetModuleHandle(const base::FilePath &dllpath);

private:
    std::map<base::FilePath, scoped_refptr<ModuleHandle>> m_modules;
    
  base::Lock m_lock;
	base::FilePath m_pathParent;
};

#endif // #ifndef __PrgCOMModuleLoader_H_1664FAA8_8E1F_4AEE_9E6B_63562BDAE418_INCLUDED__
