package com.hpe.foreground.servlet;

import cn.itcast.servlet.BaseServlet;


import java.io.IOException;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.hpe.foreground.newsdomain.MinNews2;
import com.hpe.foreground.newsdomain.NewsType;
import com.hpe.foreground.service.NewsTypeService;


@WebServlet("/NewsServlet")
public class NewsServlet extends BaseServlet {
	
	private static final long serialVersionUID = 1L;
	
	private NewsTypeService newsTypeService = new NewsTypeService();
	
	
	public void findAll(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException {
		request.setAttribute("newsList", newsTypeService.findAll());
		request.getRequestDispatcher("/foreground/common/head.jsp").include(request, response);
		
		}
	
	
	
	public void findNews(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException {
		Map<Integer, List<MinNews2>> map = new HashMap<Integer, List<MinNews2> >();
		List<NewsType> a  = newsTypeService.findAll();
		for(int i =0;i<newsTypeService.findCount();i++) {
			
			
			
			map.put(i+1, newsTypeService.findNews(a.get(i).getNewsTypeId()));
			
			
			
		}
		request.setAttribute("new1", map);
		
		request.setAttribute("count", newsTypeService.findCount());
		request.setAttribute("type", newsTypeService.findAll());
		
		
		request.getRequestDispatcher("/foreground/common/body.jsp").include(request, response);
		
		
		}
	
	
	
	public String show(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String typeI = request.getParameter("typeId");
		System.out.println("1"+typeI+"1");
		
		
		
		
		if(typeI!=null) {
			int typeId = Integer.parseInt(typeI);
			request.setAttribute("flag", "1");
			
			request.setAttribute("newsLists", newsTypeService.findNewsByTypeId(typeId));
			
		}
		request.setAttribute("newnews", newsTypeService.findNew());
		request.setAttribute("hotnews", newsTypeService.findHot());
		
		
		
		
		return "f:/foreground/newsTemp.jsp";
		
	}
	
	
	
	public String show1(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		
		String newId = request.getParameter("newsId");
	
		
		
		 if(newId!=null) {
			
			int newsId = Integer.parseInt(newId);
			
			request.setAttribute("flag", "0");
			request.setAttribute("newsContent", newsTypeService.findNewsByNewsId(newsId));
		}
		
		
		return "f:/foreground/newsTemp.jsp";
		
	}
	
	
	
}
