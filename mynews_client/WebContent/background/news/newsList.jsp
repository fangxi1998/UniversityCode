<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<!DOCTYPE html >
<html>
<head>
<base href="<%=basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script src="js/ckeditor/ckeditor.js"></script>
<script src="js/My97DatePicker/WdatePicker.js"></script>
<script type="text/javascript">



function p_del() { 
var msg = "您真的确定要删除吗？\n\n请确认！"; 
if (confirm(msg)==true){ 
return true; 
}else{ 
return false;
} 
} 

</script>
<title>新闻维护</title>

</head>
<body>
	<div class="data_list backMain">
		<div class="search_content" style="vertical-align: middle;">
			
		</div>
		<div class="data_content">
			<table class="table table-hover table-bordered">
				<tr>
					
					<th>序号</th>
					<th>新闻标题</th>
					<th>新闻类别</th>
					<th>发布时间</th>
					<th>操作</th>
				</tr>
				<c:forEach items="${NewsList}" var="newsList">
				<tr>
					
					<td>${newsList.newsId}</td>
					<td>${newsList.title}</td>
					<td>${newsList.typeName}</td>
					<td>${newsList.publishDate}</td>
					<td>
						<a href='<c:url value ='/NewsManagerServlet?method=preNews&NewsId=${newsList.newsId}&typeId=${newsList.typeId}'/>' ><button class="btn  btn-info" type="button">修改</button></a>&nbsp;
						<a href='<c:url value ='/NewsManagerServlet?method=DeleteNews&NewsId=${newsList.newsId}'/>'  
						onclick="javascript:return p_del()"><button class="btn btn-danger" type="button">
						删除</button></a>
					</td>
				</tr>
				</c:forEach>
			
			
			</table>
		</div>

		<div class="pagination pagination-centered"></div>
	</div>
</body>
</html>