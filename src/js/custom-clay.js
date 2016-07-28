module.exports = function(minified) {
  var clayConfig = this;
	
	clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function(){
		var customText = clayConfig.getItemById('custom');
		customText.hide();
	
		var customSelected = clayConfig.getItemById('dropdown');
		customSelected.on('change', function(){
			if(customSelected.get() === "8") customText.show();
			else customText.hide();
		});
	});
};