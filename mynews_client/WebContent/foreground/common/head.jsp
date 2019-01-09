<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<div class="row-fluid">
      <div class="logo">
          <div class="logo_img">
              <img src="images/logo.jpg" width="80px" alt="闪电新闻网" title="闪电新闻网" />
              <h2 style="font-family:Arial;position: absolute; left: 200px; top:30px;">闪电新闻网 </h2>
          </div>
          <div class="weather">
            <iframe allowtransparency="true" frameborder="0" width="385" height="96" scrolling="no" src="//tianqi.2345.com/plugin/widget/index.htm?s=1&z=1&t=0&v=0&d=3&bd=0&k=&f=004000&ltf=009944&htf=cc0000&q=1&e=1&a=1&c=54827&w=385&h=96&align=right"></iframe>
          </div>
          
      </div>
</div>
<div class="row-fluid">
	<div class="span12">
		<div class="navbar">
		  <div class="navbar-inner">
		   
		     <a class="brand" href="index">首页</a>
		     <ul class="nav">
		     
		    
		    <c:forEach items ="${newsList}" var ="newsType">
		    <li>

	<a href="<c:url value='/NewsServlet?method=show&typeId=${newsType.newsTypeId}'/>"> 
	${newsType.typeName} </a> 
	</li>

</c:forEach>
</ul>
		    	
		    
		  </div>
		</div>
	</div>
</div>