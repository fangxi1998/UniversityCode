package com.hpe.background.domain;

public class NewsType {
	private Integer newsTypeId;
	private String typeName;
	
	public Integer getNewsTypeId() {
		return newsTypeId;
	}
	public void setNewsTypeId(Integer newsTypeId) {
		this.newsTypeId = newsTypeId;
	}
	public String getTypeName() {
		return typeName;
	}
	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}
	@Override
	public String toString() {
		return "NewsType [newsTypeId=" + newsTypeId + ", typeName=" + typeName + "]";
	}
	
	

}
