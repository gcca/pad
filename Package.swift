// swift-tools-version: 6.2

import PackageDescription

let package = Package(
  name: "Pad",
  platforms: [
    .macOS(.v15),
    .iOS(.v18),
    .watchOS(.v11),
  ],
  targets: [
    .target(
      name: "CPad",
      path: "pad",
      sources: ["pad.cpp", "tokenizer.cpp", "parser.cpp"],
      publicHeadersPath: ".",
      cxxSettings: [
        .unsafeFlags(["-std=c++23"]),
      ]
    ),
    .executableTarget(
      name: "PadApp",
      dependencies: ["CPad"],
      path: "Sources/PadApp",
      exclude: ["Info.plist"],
      linkerSettings: [
        .unsafeFlags([
          "-Xlinker", "-sectcreate",
          "-Xlinker", "__TEXT",
          "-Xlinker", "__info_plist",
          "-Xlinker", "Sources/PadApp/Info.plist",
        ]),
      ]
    ),
  ]
)
