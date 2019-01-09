package com.hpe.foreground.service;
import java.util.List;

import com.hpe.foreground.dao.NewsTypeDao;
import com.hpe.foreground.newsdomain.MinNews;
import com.hpe.foreground.newsdomain.MinNews2;
import com.hpe.foreground.newsdomain.NewsContent;
import com.hpe.foreground.newsdomain.NewsType;

public class NewsTypeService {
	private NewsTypeDao newsTypeDao = new NewsTypeDao(); 
	public int findCount() {
		
		return newsTypeDao.count();
		
	}

	public List<MinNews> findHot() {
		
		return newsTypeDao.findHot();
	}
	
	
	public List<MinNews> findNew() {
		
		return newsTypeDao.findNew();
	}
	
	
	public List<NewsType> findAll() {
		
		return newsTypeDao.findAll();
	}
	
	
	public List<MinNews2> findNews(int typeId){
		
		return newsTypeDao.findNews(typeId);
		
		
	}
	
	
	public List<MinNews> findNewsByTypeId(int typeId){
		
		return newsTypeDao.findByTypeId(typeId);
		
		
		
	}
	
	
	public NewsContent findNewsByNewsId(int newsId){
		return newsTypeDao.findByNewsId(newsId);
		
		
		
	}

	
}
