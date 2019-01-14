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
<base href="<%= basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script src="js/ckeditor/ckeditor.js"></script>
<title>新闻管理</title>
<script type="text/javascript">
	
</script>
</head>
<body>
<h5 align="center"><span style="color:red;font-weight:900">${mes}</span></h5>
<div class="data_list backMain">
 
	<div class="data_content">
		
		 <form id="formNews" action="<c:url value='/NewsManagerServlet'/>" method="post">
		 <input type="hidden" name="method" value="UpdateNews"/>
		 <input type="hidden" name="newsId" value="${news.newsId}"/>
		
			<table style="padding: 5;width: 100%">
				<tr>
					<td width="80px">
						<label>新闻标题：</label>
					</td>
					<td>
						<input type="text" id="title" name="title" class="input-xxlarge" value="${news.title}"/>
						<font id="errorTitle" color="red"></font>
					</td>
				</tr>
				<tr>
					<td>
						<label>新闻作者：</label>
					</td>
					<td>
						<input type="text" id="author" name="author" value="${news.author}"/>
						<font id="errorAuthor" color="red"></font>
					</td>
				</tr>
				<tr>
					<td>
						<label>新闻类别：</label>
					</td>
					<td>
						<select id="typeId" name="typeId">
							
							<c:forEach items ="${type}" var ="type">
								<option value="${type.newsTypeId}" >
								${type.typeName}
								
								</option>
								</c:forEach>
								
						</select>
						<font id="errorType" color="red"></font>
					</td>
				</tr>
				<tr>
					<td>
						<label>新闻属性：</label>
					</td>
					<td>
						<label class="checkbox inline">
						  <input type="checkbox" id="isHead" name="isHead" >头条
						</label>
						<label class="checkbox inline">
						  <input type="checkbox" id="isHot" name="isHot" >热点
						</label>
					</td>
				</tr>
				<tr>
					<td valign="top">
						<label>新闻内容：</label>
					</td>
					<td>
						<textarea class="ckeditor" id="content" name="content">${news.content}</textarea>
					</td>
				</tr>
				<tr>
					<td>
						<input type="hidden" id="newsId" name="newsId" value=""/>&nbsp;
					</td>
					<td>
						<input type="submit" id="btnSubmit" class="btn btn-primary" value="保存新闻"/>&nbsp;&nbsp;
						<input type="button" class="btn btn-primary" value="返回" onclick="javascript:history.back()"/>&nbsp;&nbsp;<font id="errorContent" color="red"></font>
					</td>
				</tr>
			</table>
		</form>
	</div>
</div>	
</body>
</html>