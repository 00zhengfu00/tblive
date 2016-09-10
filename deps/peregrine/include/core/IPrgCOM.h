//------------------------------------------------------------------------------
//
//    ��Ȩ����(C) ����Ͱͣ��й������缼�����޹�˾ ��������Ȩ��
//
//    ������:   ����
//    ��������: 2015-01-29
//    ��������: �ṩ��ƽ̨�������ļ��Ķ��󴴽�����������Windows��COM�Ľ��������
//
//
//------------------------------------------------------------------------------

/**
* @class IPrgCOM
* @brief
* @author ����
* @version 1.0.0
*/

#ifndef __IPrgCOM_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__
#define __IPrgCOM_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__

#include "string"
#include "base/namespace.h"
#include "base/prg.h"
#include "base/memory/iref_counted.h"
#include "base/memory/ref_counted.h"
#include "list"
#include "base/files/file_path.h"

BEGIN_NAMESPACE(prg)

class CPrgCOMObjectIdentify:public base::RefCountedThreadSafe<CPrgCOMObjectIdentify>
{
public:
    CPrgCOMObjectIdentify();

	std::string clsid;
	std::string name;
	std::string desc;
	std::string dllname;
	bool enable;
	std::list<scoped_refptr<CPrgCOMObjectIdentify>> dependency;
    
private:
    friend class base::RefCountedThreadSafe<CPrgCOMObjectIdentify>;
    ~CPrgCOMObjectIdentify();
};
inline CPrgCOMObjectIdentify::CPrgCOMObjectIdentify():enable(true){}
inline CPrgCOMObjectIdentify::~CPrgCOMObjectIdentify(){}

class IPrgCOM:public base::IRefCounted
{
public:

     /**
     * @brief ��ʼ��COM��
     * @param path ����·����PrgCOM��ɨ����µ�����dll(Windows�µ�dll,MacOS�µ�dylib)����ȡģ��������ϵ����PrgCOMObjectIdentifies.xml�ļ�������д�xml�ļ������ظ�ɨ�衣
	 * PrgCOM���ȡPrgDisableCOM.xml����ʼ����ǰӦ�ü�����Ҫ���ص�ģ���б�
     */
    virtual HRESULT Init(const base::FilePath &path) = 0;
	
	 /**
     * @brief ��ʼ���Զ��壨����ÿ����½�˺���أ���PrgDisableCOM.xml,����һ�������ڿ��Զ������Զ��壬������Ҫ����configid
     * @param userPath ����·����PrgCOM���ȡPrgDisableCOM�������Զ���Ĳ��ܼ��ص�ģ���б�
     */
	virtual HRESULT InitCustomPrgCOMObjectConfig(const base::FilePath &userPath, const std::string &configid = "Id1") = 0;

    /**
    * @brief ����ʼ��COM��
    */
    virtual HRESULT Uninit() = 0;

    /**
    * @brief ����һ���µ�COMʵ��
    * @param clsid COMʵ��classid 
    * @param iid ʵ������ȡ�Ľӿ� 
    * @param ppObject ʵ���ӿ� 
	* @param configid �Զ����COM���ز���id
    * @return hresult_define.h
    * @remark 
    */
    virtual HRESULT CreateInstance(const std::string &clsid, const std::string &iid, void **ppObject, const std::string &configid = "") = 0;
    
    /**
    * @brief ��ȡCOMʵ�����������Get��������Cache����Ȼ�����µ�ʵ��
    * @param clsid COMʵ��classid 
    * @param name ��������ʵ������
    * @param iid ʵ������ȡ�Ľӿ� 
    * @param ppObject ʵ���ӿ�
	* @param configid �Զ����COM���ز���id
	* @param groupId �������id�����ڻ���Ķ������
    * @return hresult_define.h
    * @remark 
    */
    virtual HRESULT GetInstance(const std::string &clsid, const std::string &name, const std::string &iid, void **ppObject, const std::string &configid = "", const std::string &groupId = "") = 0;
    
    /**
    * @brief �ж�Cache�����Ƿ��д�COMʵ��
    * @param clsid COMʵ��classid 
    * @param name ��ѯ�ʵ�ʵ������
    * @param bHas �Ƿ���� 
	* @param groupId �������id�����ڻ���Ķ������
    * @return S_OK
    * @remark 
    */
    virtual HRESULT HasInstance(const std::string &clsid, const std::string &name, bool *bHas, const std::string &groupId = "") = 0;
    
    /**
    * @brief ɾ��Cache���е�ʵ��
    * @param clsid COMʵ��classid 
    * @param name ��ɾ����ʵ������
	* @param groupId �������id�����ڻ���Ķ������
    * @return S_OK
    * @remark 
    */
    virtual HRESULT DropInstance(const std::string &clsid, const std::string &name, const std::string &groupId = "") = 0;

	/**
    * @brief ɾ��Cache���д˷����µ�����ʵ��
	* @param groupId �������id�����ڻ���Ķ������
    * @return S_OK
    * @remark 
    */
	virtual HRESULT DropInstanceGroup(const std::string &groupId = "") = 0;
	/**
    * @brief �Ƿ�������ʵ��
    * @return S_OK
    * @remark 
    */
	virtual HRESULT CanCreateInstance(const std::string &clsid, bool *bCan, const std::string &configid = "") = 0;

	/**
    * @brief ��ȡ��ǰPrgCOM��������ϵ��
    * @return S_OK
    * @remark 
    */
	virtual HRESULT GetPrgCOMObjectConfig(std::list<scoped_refptr<CPrgCOMObjectIdentify>> &listPrgCOMObject, const std::string &configid = "") = 0;

	/**
    * @brief �����û��Զ����disable����ģ��
	* @param configid �Զ����COM���ز���id
    * @return S_OK
    * @remark 
    */
	virtual HRESULT ResetCustomPrgCOMObjectConfig(const std::string &configid = "Id1") = 0;

	/**
    * @brief �����û��Զ����disable����ģ��
	* @param configid �Զ����COM���ز���id
    * @return S_OK
    * @remark 
    */
	virtual HRESULT EnableCustomPrgCOMObjectConfig(const std::string &clsid, bool enable = true, const std::string &configid = "Id1") = 0;
};

END_NAMESPACE()
#endif // #ifndef __IPrgCOM_H_75895926_20F7_40B4_A1F4_718D2F4AFFA1_INCLUDED__
