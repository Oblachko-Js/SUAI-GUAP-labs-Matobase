<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  <head>
    <title>Каталог роботов-игрушек (построчное представление)</title>
    <style>
      .robot {
        border: 1px solid #ddd;
        margin: 10px 0;
        padding: 15px;
        border-radius: 5px;
      }
      .robot-header {
        display: flex;
        align-items: center;
        margin-bottom: 10px;
      }
      .robot-image {
        margin-right: 20px;
      }
      img {
        max-width: 120px;
        max-height: 120px;
      }
      .robot-info {
        flex-grow: 1;
      }
      .robot-name {
        font-size: 1.2em;
        font-weight: bold;
        margin-bottom: 5px;
      }
      .features {
        margin-top: 10px;
        padding-left: 20px;
      }
      .feature {
        margin: 5px 0;
      }
      .top-rated {
        border: 2px solid gold;
        background-color: #fffdf5;
      }
    </style>
  </head>
  <body>
    <h2>Каталог роботов-игрушек</h2>
    <xsl:apply-templates select="catalog/robot">
      <xsl:sort select="name"/>
    </xsl:apply-templates>
  </body>
  </html>
</xsl:template>

<xsl:template match="robot">
  <div class="robot">
    <xsl:if test="rating &gt; 4.7">
      <xsl:attribute name="class">robot top-rated</xsl:attribute>
    </xsl:if>
    <div class="robot-header">
      <div class="robot-image">
        <img src="{image}" alt="{name}"/>
      </div>
      <div class="robot-info">
        <div class="robot-name"><xsl:value-of select="name"/></div>
        <div>Производитель: <xsl:value-of select="manufacturer"/></div>
        <div>Цена: <xsl:value-of select="price"/> <xsl:value-of select="price/@currency"/></div>
        <div>Возраст: <xsl:value-of select="age_range"/></div>
        <div>Вес: <xsl:value-of select="weight"/></div>
        <div>Рейтинг: <xsl:value-of select="rating"/>/5</div>
      </div>
    </div>
    <div class="features">
      <h4>Особенности:</h4>
      <xsl:for-each select="features/feature">
        <div class="feature"><xsl:value-of select="."/></div>
      </xsl:for-each>
    </div>
  </div>
</xsl:template>
</xsl:stylesheet>