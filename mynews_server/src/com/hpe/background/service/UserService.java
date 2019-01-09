package com.hpe.background.service;

import java.util.List;

import com.hpe.background.dao.UserDao;
import com.hpe.background.domain.MinNews2;
import com.hpe.background.domain.News;
import com.hpe.background.domain.NewsType;
import com.hpe.background.domain.User;



//User 的业务逻辑层
 public class UserService {
	private UserDao userDao = new UserDao();
	public void UpdateNews(News news) throws UserException {
		
		if(news.getTitle()=="") throw new UserException("标题不能为空");
		if(news.getAuthor()=="") throw new UserException("作者不能为空");
		if(news.getTypeId().equals("0")) throw new UserException("请选择新闻类型");
		if(news.getContent()=="") throw new UserException("请填写新闻内容");
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
		if(user==null)throw new UserException("用户名不存在");
		if(!user.getPassword().equals(form.getPassword()))
			throw new UserException("密码错误");
		
		
		return user;
		}
	public void NewsAdd(News news) throws UserException{
		
		System.out.println(news.getTypeId().equals("0"));
		if(news.getTitle()=="") throw new UserException("标题不能为空");
		if(news.getAuthor()=="") throw new UserException("作者不能为空");
		if(news.getTypeId().equals("0")) throw new UserException("请选择新闻类型");
		if(news.getContent()=="") throw new UserException("请填写新闻内容");
		
		userDao.NewsAdd(news);
		
		
		
	}
public void NewsTypeAdd(String typeName) throws UserException{
		
	
		
		if(typeName=="") throw new UserException("请填写新闻类别名称");
		
		userDao.NewsTypeAdd(typeName);
		
		
		
	}
public void DeleteNewsTypeByNewsId(int newsTypeId) throws UserException {
	
	if(userDao.count(newsTypeId)!=0) throw new UserException("请先把该类的新闻删除在删除该类标题");
	userDao.DeleteNewsTypeByNewsId(newsTypeId);
	
}
	
}
