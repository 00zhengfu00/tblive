//------------------------------------------------------------------------------
//
//    ��Ȩ����(C) ����Ͱͣ��й������缼�����޹�˾ ��������Ȩ��
//
//    ������:   ��ԭ
//    ��������: 2015-12-30
//    ��������:
//        scopt_ptr<CIntrusiveStrong> sp; 
//        CIntrusiveWeakRef weak(sp.get());
//
//
//------------------------------------------------------------------------------

#ifndef __IntrusiveRef_HELPER_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__
#define __IntrusiveRef_HELPER_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__

#include <base\atomic_ref_count.h>


class CIntrusiveWeakRef;
class CIntrusiveStrong
{   // ֧�� ����ʽָ��.
    friend CIntrusiveWeakRef;
    typedef base::AtomicRefCount TypeCount;
    enum {XOR_MAGIC_NUM = 0x19791130}; // ħ�����֣���������Ϸ���
    volatile base::AtomicRefCount ref_count;
    volatile base::AtomicRefCount m_orVerrifyNum; // ��������Ч�Ե�У��.
public:
    CIntrusiveStrong():ref_count(0),
        m_orVerrifyNum(XOR_MAGIC_NUM^TypeCount(this)) { }
    virtual ~CIntrusiveStrong(){ m_orVerrifyNum = ref_count = 0; }
    bool HasOneRef()
    {
        return base::AtomicRefCountIsOne(&ref_count);
    }
    TypeCount AddRef()
    {
        return base::AtomicRefCountIncN(&ref_count, 1);
    }
    TypeCount Release()
    {
        const TypeCount nRef = base::AtomicRefCountDecN(&ref_count, 1);
        if ( 0 == nRef )
        {   // ���߳̽����ʱ��, ֻ����һ������ 0 ��.
            m_orVerrifyNum = ref_count = 0;
            delete this; return 0;
        }
        return nRef > 0 ? nRef : 0;
    }
};

class CIntrusiveWeakRef
{
    CIntrusiveStrong* m_pStrongRef;
    static const long XOR_MAGIC_NUM = CIntrusiveStrong::XOR_MAGIC_NUM;
    typedef CIntrusiveStrong::TypeCount TypeCount;
public:
    virtual ~CIntrusiveWeakRef(){ m_pStrongRef = NULL; }
    CIntrusiveWeakRef(CIntrusiveStrong* pStrongRef):m_pStrongRef(pStrongRef){}
    template< class I > bool GetStrongRef( I **ppStrongRef )
    {
        if ( !m_pStrongRef || !ppStrongRef )
        {
            return false;
        }

        do
        {
            TypeCount counter = m_pStrongRef->ref_count;
            if ( counter <= 0 || m_pStrongRef->m_orVerrifyNum != (XOR_MAGIC_NUM^TypeCount(m_pStrongRef)) )
            {   // ���ü���С���㣬�����Ƕ����Ѿ���ȷ�����١�
                return false;
            }

            if (m_pStrongRef->ref_count == counter)
            {
                base::AtomicRefCountIncN(&m_pStrongRef->ref_count, 1);
                if ( m_pStrongRef->m_orVerrifyNum == (XOR_MAGIC_NUM^TypeCount(m_pStrongRef)) )
                {   // У����Ч�Գɹ�. 
                    I* pDestObject = NULL;
                    try {
                        pDestObject = dynamic_cast<I*>(m_pStrongRef);
                    } catch( ... ){ pDestObject = nullptr; return false; }

                    *ppStrongRef = pDestObject;
                    return pDestObject ? true : false;
                } return false; 
            }
        } while ( true ); return false;
    }
};
#endif // #ifndef __IntrusiveRef_HELPER_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__
