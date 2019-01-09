package com.hpe.background.service;
import java.util.List;

import com.hpe.background.dao.NewsTypeDao;
import com.hpe.background.domain.NewsContent;
import com.hpe.background.domain.NewsType;


public class NewsTypeService {
	private NewsTypeDao newsTypeDao = new NewsTypeDao(); 
	

	
	
	
	
	public List<NewsType> findAll() {
		
		return newsTypeDao.findAll();
	}
	

	
	
	public NewsContent findNewsByNewsId(int newsId){
		return newsTypeDao.findByNewsId(newsId);
		
		
		
	}

	
}
