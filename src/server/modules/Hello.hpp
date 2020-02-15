/* --- Hello.hpp --- */
#pragma once
#include <iostream>

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp>

class Hello : public oZ::IModule
{
public:
	Hello(void) = default;
	virtual ~Hello(void) = default;

	virtual const char *getName(void) const { return "Hello"; }
	virtual Dependencies getDependencies(void) const noexcept { return { "World" }; }
	
	virtual void onConnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint, const bool useEncryption) {
		std::cout << "New client connected: " << endpoint.getAddress() << std::endl;
	}
	
	virtual void onDisconnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint, const bool useEncryption) {
		std::cout << "Client diconnected: " << endpoint.getAddress() << std::endl;
	}

	// Register your callback to the pipeline
	virtual void onRegisterCallbacks(oZ::Pipeline &pipeline) {
		pipeline.registerCallback(
			oZ::State::Interpret, // Call at response creation time
			oZ::Priority::Medium + 1, // With medium priority but higher than 'World' module
			this, &Hello::onInterpret // Member function style
		);
	}

private:
	bool onInterpret(oZ::Context &context) {
		oZ::Log(oZ::Information) << "Module 'Hello' wrote successfully its message";
		context.getResponse().getHeader().set("Content-Type", "text/plain");
		context.getResponse().getBody() += "Hello";
		return true;
	}
};

