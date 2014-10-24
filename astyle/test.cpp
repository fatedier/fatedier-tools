#include "FileCliAndSrv.h"
CFileCliAndSrv app;
CFlowIntfCtrl *const theApp = &app;

CONFIG_PARAM gParam; 

CFileCliAndSrv::CFileCliAndSrv()
{
}

CFileCliAndSrv::~CFileCliAndSrv()
{
}

void CFileCliAndSrv::prepare()
{

  LOG_DEBUG(g_logger,"prepare");

	if(gParam.nFileType == 1)   //1 GET ���������
	{
      
	     if( createServerSon() != 0)
	     {
	     	   LOG_ERROR(g_logger, "�����ļ���������ӽ���ʧ�ܣ�");
	 	       return;
	     }

	}
	else if(gParam.nFileType == 2)  //2 PUT  �ͷ����ϴ�
	{ 
       
	    if(createClientSon() != 0)
	    {
	      	   LOG_ERROR(g_logger, "�����ļ����䷢���ӽ���ʧ�ܣ�");
	 	         return;
	    }
	}

}

int CFileCliAndSrv::createServerSon()
{
	   //�����ӽ��� 
	  pid_t nSonPid;
	  if( m_bRunning == false )
		  return 0; 
		  
		 CFileCliAndSrvChild *child=new CFileCliAndSrvChild;
     child->setPpid(getpid());
	   child->setCfgPrefix("child");
	   child->setDesc("�ļ������ӽ���"); 
		 //�ӽ��̱��
	   child->setChildID(8888);  
     nSonPid = forkChild(child,8888,0,1,1);
     if(nSonPid < 0)
     {
       LOG_ERROR(g_logger,"forkChild error"); 
       //return  -1;    
     } 
     else
     {       
			 LOG_INFO(g_logger,"�����ӽ��� fork process success pid = " << nSonPid<<"�ӽ��̱����[9999]");			     
		 } 
	 
	 	return 0;  
	
}

int CFileCliAndSrv::createClientSon()
{
	  
	   //�����ӽ��� 
	  pid_t nSonPid;
	  if( m_bRunning == false )
		  return 0; 
		  
		 CFileCliAndSrvChild *child=new CFileCliAndSrvChild;
     child->setPpid(getpid());
	   child->setCfgPrefix("child");
	   child->setDesc("�ļ������ӽ���"); 
		 //�ӽ��̱��
	   child->setChildID(9999);  
     nSonPid = forkChild(child,9999,0,1,1);
     if(nSonPid < 0)
     {
       LOG_ERROR(g_logger,"forkChild error"); 
       //return  -1;    
     } 
     else
     {       
			 LOG_INFO(g_logger,"�����ӽ��� fork process success pid = " << nSonPid<<"�ӽ��̱����[9999]");			     
		 } 
	 
	 	return 0;  
}


//����
void CFileCliAndSrv::handle()
{

   sleep(gParam.nInterval);
	
}


void CFileCliAndSrv::finish()
{
	LOG_DEBUG(g_logger,"finish");
}

int CFileCliAndSrv::initialize(int argc,char* argv[])
{
 
   int nRet = ERR_NONE;
   nRet = CFlowIntfCtrl::initialize(argc,argv);
   if(nRet != ERR_NONE)
     return nRet;

 //��ȡ�����ļ���Ӧ����ص���Ϣ
    if ( (nRet = readAppCfg() ) != ERR_SUCCESS)
    {
        return nRet;
    }
    return ERR_SUCCESS;

}

int CFileCliAndSrv::readAppCfg()
{
    string strBuf;
    int    nTmp;

    //nFileType
    gParam.nFileType = g_CfgMgr.getInt(m_strDomFix+".file_type",-1);
    if ( -1 == gParam.nFileType )
    {
        LOG_ERROR(g_logger, "file_type do not found!");
	    	return ERR_PUB_PARANOTFOUND;
    }
    LOG_DEBUG( g_logger, "file_type=[" << gParam.nFileType << "]" );
   if( gParam.nFileType == 2)
   {
   	   //host_port
       gParam.nHostPort = g_CfgMgr.getInt(m_strDomFix+".tcp_file_cli_Port",-1);
       if ( -1 == gParam.nHostPort )
       {
           LOG_ERROR(g_logger, "tcp_file_cli_Port do not found!");
	       	return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_cli_Port=[" << gParam.nHostPort << "]" );
       
       //host_ip
       strBuf = g_CfgMgr.getString(m_strDomFix+".tcp_file_cli_HostIP","");
       if ( "" == strBuf )
       {
           LOG_ERROR(g_logger, "tcp_file_cli_HostIP do not found!");
		       return ERR_PUB_PARANOTFOUND;
       }
       strncpy(gParam.sHostIp,strBuf.c_str(),sizeof(gParam.sHostIp));
       LOG_DEBUG( g_logger, "tcp_file_cli_HostIP=[" << gParam.sHostIp << "]" );
       
       //senddir
       strBuf = g_CfgMgr.getString(m_strDomFix+".tcp_file_cli_SendDir","");
       if ( "" == strBuf )
       {
           LOG_ERROR(g_logger, "tcp_file_cli_SendDir do not found!");
		       return ERR_PUB_PARANOTFOUND;
       }
       gParam.sSendDir=strBuf;
       LOG_DEBUG( g_logger, "tcp_file_cli_SendDir=[" << gParam.sSendDir << "]" );
       
        //interval
       gParam.nInterval = g_CfgMgr.getInt(m_strDomFix+".tcp_file_cli_Interval",-1);
       if ( -1 == gParam.nInterval )
       {
           LOG_ERROR(g_logger, "tcp_file_cli_Interval do not found!");
	       	return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_cli_Interval=[" << gParam.nInterval << "]" );
       
       //timetolive
       gParam.nTimeToLive = g_CfgMgr.getInt(m_strDomFix+".tcp_file_cli_TimeToLive",-1);
       if ( -1 == gParam.nTimeToLive )
       {
           LOG_ERROR(g_logger, "tcp_file_cli_TimeToLive do not found!");
	       	return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_cli_TimeToLive=[" << gParam.nTimeToLive << "]" );
       
       gParam.nCliNet = g_CfgMgr.getInt(m_strDomFix+".tcp_file_cli_network",-1);
       if ( -1 == gParam.nCliNet )
       {
       	  LOG_ERROR(g_logger, "tcp_file_cli_network do not found!");
           return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_cli_network=[" << gParam.nCliNet << "]" );
   }
   else
   {
       //srv_port
       gParam.nSrvPort = g_CfgMgr.getInt(m_strDomFix+".tcp_file_srv_Port",-1);
       if ( -1 == gParam.nSrvPort )
       {
           LOG_ERROR(g_logger, "tcp_file_srv_Port do not found!");
	       	return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_srv_Port=[" << gParam.nSrvPort << "]" );
       
       //rcvdir
       strBuf = g_CfgMgr.getString(m_strDomFix+".tcp_file_srv_RcvDir","");
       if ( "" == strBuf )
       {
           LOG_ERROR(g_logger, "tcp_file_srv_RcvDir do not found!");
		       return ERR_PUB_PARANOTFOUND;
       }
       gParam.sSrvRcvDir=strBuf;
       LOG_DEBUG( g_logger, "tcp_file_srv_RcvDir=[" << gParam.sSrvRcvDir << "]" );
       
       //tmpdir
       strBuf = g_CfgMgr.getString(m_strDomFix+".tcp_file_srv_TmpDir","");
       if ( "" == strBuf )
       {
           LOG_ERROR(g_logger, "tcp_file_srv_TmpDir do not found!");
		       return ERR_PUB_PARANOTFOUND;
       }
       gParam.sSrvTmpDir=strBuf;
       LOG_DEBUG( g_logger, "tcp_file_srv_TmpDir=[" << gParam.sSrvTmpDir << "]" );
       
       //nSrvSleepTime
       gParam.nSrvSleepTime = g_CfgMgr.getInt(m_strDomFix+".tcp_file_srv_sleep_time",-1);
       if ( -1 == gParam.nSrvSleepTime )
       {
       	  LOG_ERROR(g_logger, "tcp_file_srv_sleep_time do not found!");
           gParam.nSrvSleepTime =1;
       }
       LOG_DEBUG( g_logger, "tcp_file_srv_sleep_time=[" << gParam.nSrvSleepTime << "]" );
       
       gParam.nSrvNet = g_CfgMgr.getInt(m_strDomFix+".tcp_file_srv_network",-1);
       if ( -1 == gParam.nSrvNet )
       {
       	  LOG_ERROR(g_logger, "tcp_file_srv_network do not found!");
           return ERR_PUB_PARANOTFOUND;
       }
       LOG_DEBUG( g_logger, "tcp_file_srv_network=[" << gParam.nSrvNet << "]" );       
      
   }
    return ERR_SUCCESS;
}
