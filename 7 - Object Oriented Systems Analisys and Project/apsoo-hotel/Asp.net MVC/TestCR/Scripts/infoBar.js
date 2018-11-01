//Copyright (c) 2008 Lewis Linn White Jr.
//Author: Lewis Linn White Jr.

//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this software and associated documentation
//files (the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions:

//The above copyright notice and this permission notice shall be
//included in all copies or substantial portions of the Software.
//Except as contained in this notice, the name(s) of the above 
//copyright holders shall not be used in advertising or otherwise 
//to promote the sale, use or other dealings in this Software without 
//prior written authorization.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.

//Icons used in this project are graciously provided by the Silk icons set:
//http://www.famfamfam.com/lab/icons/silk/

function infoBar(settings)
{
	//test to see if we can support this
	if(!document.createElement)
	{
		alert('I\'m sorry, but your browser doesn\'t support this feature.');
		return;
	}
	//create an empty settings object if one isn't provided
	if(!settings)
	{
		settings = {};
	}
	
	//ie6 doesn't support the 'fixed' css position, so will will have to hack around it
	var ie6 = (document.all && window.external && (typeof document.documentElement.style.maxHeight == 'undefined')) ? true : false;	
	
	//Create and setup the info bar
	var infoBarDiv = document.createElement('div');
	this.currentOpacity = 10;
	this.infoBar = infoBarDiv;
	infoBarDiv.style.backgroundColor = settings.backColor || '#fff68f';
	infoBarDiv.style.opacity = '1';
	infoBarDiv.style.filter = 'alpha(opacity=100)';
	infoBarDiv.style.fontSize = '8pt';
	infoBarDiv.style.top = '0px';
	infoBarDiv.style.left = '0px';
	infoBarDiv.style.lineHeight = '12px';
	infoBarDiv.style.padding = '0px';
	infoBarDiv.style.width = '100%';
	infoBarDiv.style.fontFamily = 'Verdana';
	infoBarDiv.style.fontColor = settings.fontColor || '#000000';
	//ie6 doesn't support the 'fixed' css position, so will will have to hack around it
	infoBarDiv.style.position = (ie6) ? 'absolute' : 'fixed';
	infoBarDiv.style.display = 'none';
	infoBarDiv.style.border = '1px solid #000000';
	infoBarDiv.style.borderTop = '0px';
	infoBarDiv.style.borderLeft = '0px';
	infoBarDiv.style.borderRight = '0px';
	infoBarDiv.style.zIndex = 1000;
	//ie6 doesn't support the 'fixed' css position, so will will have to hack around it
	if(ie6)
	{
		window.onscroll = function()
		{
			infoBarDiv.style.top = parseInt(window.pageYOffset || (document.documentElement.scrollTop || 0), 10) + 'px';
			infoBarDiv.style.left = parseInt(window.pageXOffset || (document.documentElement.scrollLeft || 0), 10) + 'px';
		};
	}
	
	//Create our icon
	var icon = document.createElement('img');
	this.infoBar.icon = icon;
	icon.src = resolveUrl('~/Content/images/exclamation.png');
	icon.style.cssFloat = 'left';
	icon.style.styleFloat = 'left';  //for IE
	icon.style.verticalAlign = 'middle';
	icon.style.paddingTop = '3px';
	icon.style.paddingLeft = '3px';
	icon.style.paddingRight = '3px';
	icon.style.paddingBottom = '3px';
	
	//Create our close button 
	var close = document.createElement('img');
	close.src = resolveUrl('~/Content/images/cross.png');
	close.style.cssFloat = 'right';
	close.style.styleFloat = 'right'; //for IE
	close.style.verticalAlign = 'middle';
	close.style.paddingTop = '3px';
	close.style.paddingBottom = '3px';
	close.style.cursor = 'pointer';
	close.onclick = function()
	{
		infoBarDiv.style.display = 'none';
	};
	
	//Create our text entry
	var infoText = document.createElement('div');
	this.infoBar.infoText = infoText;
	infoText.innerHTML = settings.text || '';
	infoText.style.paddingTop = '3px';
	infoText.style.paddingBottom = '3px';
	infoText.style.color = "#000000";
	infoText.style.paddingTop = '5px';
	
	infoBarDiv.appendChild(close);
	infoBarDiv.appendChild(icon);
	infoBarDiv.appendChild(infoText);
	document.body.insertBefore(infoBarDiv, document.body.firstChild);
}

infoBar.prototype.show = function(fade)
{
	var that = this;
	if(typeof fade == "number")
	{
		this.currentOpacity = 0;
		this.infoBar.style.opacity = '0';
		this.infoBar.style.filter = 'alpha(opacity=0)';
		this.intervalID = window.setInterval(function()
											{
													if(that.currentOpacity < 11)
													{
														that.infoBar.style.opacity = that.currentOpacity / 10;
														that.infoBar.style.filter = 'alpha(opacity=' + that.currentOpacity * 10 + ')';
														that.currentOpacity++;
													}
													else
													{
														window.clearInterval(that.intervalID);
													}
											}, fade);
	}
	else
	{
		this.infoBar.style.opacity = '1';
		this.infoBar.style.filter = 'alpha(opacity=100)';
	}
	this.infoBar.style.display = 'block';
};

infoBar.prototype.setText = function(newText)
{
	this.infoBar.infoText.innerHTML = newText;
};

infoBar.prototype.setIcon = function(newIcon)
{
	this.infoBar.icon.src = newIcon + '.png';
};

infoBar.prototype.setFontColor = function(fontColor)
{
	this.infoBar.infoText.style.color = fontColor;
};

infoBar.prototype.setBackColor = function(backColor)
{
	this.infoBar.style.backgroundColor = backColor;
};

infoBar.prototype.hide = function()
{
	this.infoBar.style.display = 'none';
};

infoBar.prototype.destroy = function()
{
	document.body.removeChild(this.infoBar);
};