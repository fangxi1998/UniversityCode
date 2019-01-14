package com.hpe.background.service;

import java.util.List;

import com.hpe.background.dao.UserDao;
import com.hpe.background.domain.MinNews2;
import com.hpe.background.domain.News;
import com.hpe.background.domain.NewsType;
import com.hpe.background.domain.User;



//User ��ҵ���߼���
 public class UserService {
	private UserDao userDao = new UserDao();
	public void UpdateNews(News news) throws UserException {
		
		if(news.getTitle()=="") throw new UserException("���ⲻ��Ϊ��");
		if(news.getAuthor()=="") throw new UserException("���߲���Ϊ��");
		if(news.getTypeId().equals("0")) throw new UserException("��ѡ����������");
		if(news.getContent()=="") throw new UserException("����д��������");
		userDao.UpdateNews(news);
	}
	
	public void UpdateNewsType(NewsType newsType) {
		
		userDao.UpdateNewsType(newsType);
		
	}
	
	public void DeleteNewsByNewsId(int newsId) {
		
		userDao.DeleteNewsByNewsId(newsId);
		
	}
	public List<NewsType> findnewsType(String id){
		
		 return userDao.findnewsType(id);
		
	}
	
	public List<MinNews2> findNews(){
		 
		
		return userDao.findNews();
	}
	public User login(User form ) throws UserException{
		User user = userDao.findByUsername(form.getUserName());
		if(user==null)throw new UserException("�û���������");
		if(!user.getPassword().equals(form.getPassword()))
			throw new UserException("�������");
		
		
		return user;
		}
	public void NewsAdd(News news) throws UserException{
		
		System.out.println(news.getTypeId().equals("0"));
		if(news.getTitle()=="") throw new UserException("���ⲻ��Ϊ��");
		if(news.getAuthor()=="") throw new UserException("���߲���Ϊ��");
		if(news.getTypeId().equals("0")) throw new UserException("��ѡ����������");
		if(news.getContent()=="") throw new UserException("����д��������");
		
		userDao.NewsAdd(news);
		
		
		
	}
public void NewsTypeAdd(String typeName) throws UserException{
		
	
		
		if(typeName=="") throw new UserException("����д�����������");
		
		userDao.NewsTypeAdd(typeName);
		
		
		
	}
public void DeleteNewsTypeByNewsId(int newsTypeId) throws UserException {
	
	if(userDao.count(newsTypeId)!=0) throw new UserException("���ȰѸ��������ɾ����ɾ���������");
	userDao.DeleteNewsTypeByNewsId(newsTypeId);
	
}
	
}
