if(MSVC OR XCODE)
	file(GLOB SOURCE_FILES src/Common/*)
	source_group("Source Files\\Common" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Common/impl/*)
	source_group("Source Files\\Common\\impl" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/ConFuoco/*)
	source_group("Source Files\\ConFuoco" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/ConFuoco/Codecs/*)
	source_group("Source Files\\ConFuoco\\Codecs" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/ConFuoco/impl/*)
	source_group("Source Files\\ConFuoco\\impl" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/FileSystem/*)
	source_group("Source Files\\FileSystem" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Graphics/*)
	source_group("Source Files\\Graphics" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Graphics/Decoders/*)
	source_group("Source Files\\Graphics\\Decoders" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Graphics/Shaders/*)
	source_group("Source Files\\Graphics\\Shaders" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Heimdall/*)
	source_group("Source Files\\Heimdall" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Heimdall/impl/*)
	source_group("Source Files\\Heimdall\\impl" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Input/*)
	source_group("Source Files\\Input" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Input/impl/*)
	source_group("Source Files\\Input\\impl" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Lua/*)
	source_group("Source Files\\Lua" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Platform/*)
	source_group("Source Files\\Platform" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Platform/impl/*)
	source_group("Source Files\\Platform\\impl" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Resources/*)
	source_group("Source Files\\Resources" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/Tests/*)
	source_group("Source Files\\Tests" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Tests/Common/*)
	source_group("Source Files\\Tests\\Common" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Tests/ConFuoco/*)
	source_group("Source Files\\Tests\\ConFuoco" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Tests/FileSystem/*)
	source_group("Source Files\\Tests\\FileSystem" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Tests/Input/*)
	source_group("Source Files\\Tests\\Input" FILES ${SOURCE_FILES})
	file(GLOB SOURCE_FILES src/Tests/Resources/*)
	source_group("Source Files\\Tests\\Resources" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/ThirdParty/Box2D/*)
	source_group("Source Files\\ThirdParty\\Box2D" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/ThirdParty/Spine/*)
	source_group("Source Files\\ThirdParty\\Spine" FILES ${SOURCE_FILES})

	file(GLOB SOURCE_FILES src/ThirdParty/TestFlight/*)
	source_group("Source Files\\ThirdParty\\TestFlight" FILES ${SOURCE_FILES})

	set(SOURCE_FILES)
endif()
