<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<!DOCTYPE html >
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>闪电新闻网</title>
<link href="style/news.css" rel="stylesheet">
<link href="style/index.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
</head>
<body>
<div class="container">
<jsp:include page='${"/NewsServlet?method=findAll"}'></jsp:include>

<div class="row-fluid">
<c:choose>
<c:when test="${flag == '1'}">
	<div class="span8">
		<div class="data_list">
	<div class="datas news_type_list">
		<ul>
		<c:forEach items ="${newsLists}" var ="newsLists">
		    <li>

	<span>${newsLists.publishDate}</span>&nbsp;&nbsp;
				<a href="<c:url value='/NewsServlet?method=show1&newsId=${newsLists.newsId}'/>">${newsLists.title}</a>
	</li>

</c:forEach>
			<li>
				
			</li>
			
		</ul>
	</div>
</div>
	</div>
	
		<div class="span4">
		<div class="data_list right_news_list">
			<div class="dataHeader">最新新闻</div>
			<div class="datas">
				<ul>
				<c:forEach items ="${newnews}" var ="newnews">
				<li><a href="<c:url value='/NewsServlet?method=show1&newsId=${newnews.newsId}'/>">${newnews.title}</a></li>
				</c:forEach>
					
					
				</ul>
			</div>
		</div>
		<div class="data_list right_news_list">
			<div class="dataHeader">最热新闻</div>
			<div class="datas">
				<ul>
					<c:forEach items ="${hotnews}" var ="hotnews">
				<li><a href="<c:url value='/NewsServlet?method=show1&newsId=${hotnews.newsId}'/>">${hotnews.title}</a></li>
				</c:forEach>
				</ul>
			</div>
		</div>
		
		
	</div>
	
		
	
	</c:when>
	<c:when test="${flag == '0'}">
	<div class="data_list">
	<div>
		<div class="news_title"><h3>${newsContent.title}</h3></div>
		<div class="news_info">
			发布时间：[${newsContent.publishDate } ]&nbsp;&nbsp;作者：${newsContent.author}
			&nbsp;&nbsp;新闻类别：${newsContent.typeName}&nbsp;&nbsp;
		</div>
		<div class="news_content">
			${newsContent.content}
		</div>
	</div>
</div>
	</c:when>
	
	</c:choose>

</div>

<jsp:include page="/foreground/common/foot.jsp"/>
</div>
</body>
</html>