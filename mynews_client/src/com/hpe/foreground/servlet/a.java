package com.hpe.foreground.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.hpe.foreground.service.NewsTypeService;

@WebServlet("/news")
public class a extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private NewsTypeService newsTypeService = new NewsTypeService();
	
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		this.doPost(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String typeI = request.getParameter("typeId");
		int typeId = Integer.parseInt(typeI);
		String action = request.getParameter("action");
		if("list".equals(action)){
			
			request.setAttribute("mainPage", "news/newsList.jsp");
		}else if("detail".equals(action)){
		
			request.setAttribute("mainPage", "news/newsShow.jsp");
		}
		
		request.setAttribute("newsLists", newsTypeService.findNewsByTypeId(typeId));
		
		request.getRequestDispatcher("foreground/newsTemp.jsp").forward(request, response);
	}
}
