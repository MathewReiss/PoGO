module.exports = [
	{
		"type" : "heading",
		"defaultValue" : "Pokemon GO Settings"
	},
	{
		"type" : "section",
		"items" : [
			{
				"type" : "color",
				"messageKey" : "BackgroundColor",
				"defaultValue" : "0xFFFFFF",
				"label" : "Background Color",
			},
			{
				"type" : "select",
				"messageKey" : "Team",
				"label" : "Choose Team",
				"defaultValue" : "0",
				"options" : [
					{
						"value" : "0",
						"label" : "PoGO Logo"
					},
					{
						"value" : "1",
						"label" : "Valor"
					},
					{
						"value" : "2",
						"label" : "Mystic"
					},
					{
						"value" : "3",
						"label" : "Instinct"
					}
				]
			},
			{
				"type" : "toggle",
				"messageKey" : "ShowBattery",
				"label" : "Show Battery Indicator",
				"defaultValue" : false
			},
			{
				"type" : "select",
				"messageKey" : "Optional",
				"label" : "Additional Info",
				"defaultValue" : "0",
				"id" : "dropdown",
				"capabilities" : ["COLOR", "RECT"],
				"options" : [
					{
						"value" : "0",
						"label" : "Nothing"
					},
					{
						"value" : "1",
						"label" : "Team Name"
					},
					{
						"value" : "2",
						"label" : "Date (MM/DD/YY)"
					},
					{
						"value" : "3",
						"label" : "Date (DD/MM/YY)"
					},
					{
						"value" : "4",
						"label" : "Steps (1,000)"
					},
					{
						"value" : "5",
						"label" : "Steps (1.000)"
					},
					{
						"value" : "6",
						"label" : "Distance (1.25)"
					},
					{
						"value" : "7",
						"label" : "Distance (1,25)"
					},
					{
						"value" : "8",
						"label" : "Custom Text"
					}
				]
			},
			{
				"type" : "select",
				"messageKey" : "Optional",
				"label" : "Additional Info",
				"defaultValue" : "0",
				"id" : "dropdown",
				"capabilities" : ["COLOR", "ROUND"],
				"options" : [
					{
						"value" : "0",
						"label" : "Nothing"
					},
					{
						"value" : "1",
						"label" : "Team Name"
					},
					{
						"value" : "2",
						"label" : "Date (MM/DD)"
					},
					{
						"value" : "3",
						"label" : "Date (DD/MM)"
					},
					{
						"value" : "4",
						"label" : "Steps (1,000)"
					},
					{
						"value" : "5",
						"label" : "Steps (1.000)"
					},
					{
						"value" : "6",
						"label" : "Distance (1.25)"
					},
					{
						"value" : "7",
						"label" : "Distance (1,25)"
					},
					{
						"value" : "8",
						"label" : "Custom Text"
					}
				]
			},
			{
				"type" : "input",
				"messageKey" : "CustomText",
				"defaultValue" : "",
				"label" : "Custom Text",
				"id" : "custom",
				"capabilities" : ["COLOR"]
			},
			{
				"type" : "toggle",
				"messageKey" : "Pokestop",
				"label" : "Pokestop Reminder",
				"description" : "Flick your wrist to start a 5 minute timer to remind you to revisit that Pokestop!"
			}
		]
	},
	{
		"type" : "submit",
		"defaultValue" : "Save Settings"
	}
];