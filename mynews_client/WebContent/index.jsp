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
<base href="<%=basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>闪电新闻网</title>
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<link  href="style/index.css" rel="stylesheet"/>
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script src="js/slider.js"></script> 
<script type="text/javascript">
$(function(){
	$('#focus').flexslider({
		animation: "slide",
		direction:"horizontal",
		easing:"swing"
	});
});
</script>
</head>
<body>
	<div class="container">
		<jsp:include page='${"/NewsServlet?method=findAll"}'></jsp:include>
		<div class="row-fluid">
			 <div id="focus" class="flexslider">
				<ul class="slides">
					<li><div class="img"><img src="images/focus01.jpg" /></div></li>
					<li><div class="img"><img src="images/focus02.jpg" /></div></li>
					<li><div class="img"><img src="images/focus2.jpg" /></div></li>
				</ul>
			</div>
		</div>
	<div class="row-fluid">
		<jsp:include page='${"/NewsServlet?method=findNews"}'></jsp:include>
			</div>	
			

	<jsp:include page="/foreground/common/link.jsp" />
	<jsp:include page="/foreground/common/foot.jsp" />
	</div>
</body>
</html>