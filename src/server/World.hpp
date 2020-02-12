/* --- World.hpp --- */
#pragma once

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp> // Not defined in IModule.hpp

// Second module 'World'
class World : public oZ::IModule
{
public:
	World(void) = default;
	virtual ~World(void) = default;

	virtual const char *getName(void) const { return "World"; }
	virtual Dependencies getDependencies(void) const noexcept { return { "Hello" }; }

	// Register your callback to the pipeline
	virtual void onRegisterCallbacks(oZ::Pipeline &pipeline) {
		pipeline.registerCallback(
			oZ::State::Interpret, // Call at response creation time
			oZ::Priority::Medium, // With medium priority
			[](oZ::Context &context) { // Lambda function style
				context.getResponse().getBody() += " World";
				return true;
			}
		);
	}

	virtual void onLoadConfigurationFile(const std::string &directory) {
		/* Load module's configuration if needed, using your own configuration loader */
	}
};

/* --- World.cpp --- */
#include "World.hpp"

extern "C" oZ::IModule *CreateModule(void) { return new World(); }