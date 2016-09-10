//------------------------------------------------------------------------------
//
//  ��Ȩ����(C) �㽭��è�������޹�˾ ��������Ȩ��
//
//  ������:   ����
//  ��������: 2015/02/11
//  ��������: ��֧�����ü����Ľӿڽ��м򵥷�װ
//
//------------------------------------------------------------------------------

#ifndef __IREF_COUNTED_WRAP_H_C89CB037_B3B7_4618_AAF8_B9FFD1651E9F_INCLUDED__
#define __IREF_COUNTED_WRAP_H_C89CB037_B3B7_4618_AAF8_B9FFD1651E9F_INCLUDED__

#include <base/namespace.h>
#include <base/memory/ref_counted.h>

BEGIN_NAMESPACE(prg)

template <typename Interface, typename WrapType>
class IRefcountWrapBase
{
public:
	inline IRefcountWrapBase()
	{
	}
	inline IRefcountWrapBase(Interface* that)
		: m_spInterface(that)
	{
	}
	inline operator bool() const
	{
		return (m_spInterface != NULL);
	}
	inline WrapType& operator=(Interface* pInterface) const
	{
		m_spInterface = pInterface;
		return *this;
	}
	inline operator Interface*() const
	{
		return m_spInterface;
	}
	inline Interface* operator->() const
	{
		return m_spInterface;
	}
protected:
	scoped_refptr<Interface> m_spInterface;
	typedef IRefcountWrapBase<Interface, WrapType> wrapbase;
};

END_NAMESPACE()

#endif // __IREF_COUNTED_WRAP_H_C89CB037_B3B7_4618_AAF8_B9FFD1651E9F_INCLUDED__
