include "Version.lua"

function generate_version(headerLocation)
    print("Generating version header for project...")

    local scriptDir = path.getdirectory(_SCRIPT)
    local projectRoot = path.join(scriptDir, "../..")

    os.chdir(projectRoot)

    local handle = io.popen("git log -1 --format=%cd --date=format:%Y-%m-%d")
    local date = string.gsub(handle:read("*a"), '%s+', '')
    handle:close()

    local content = string.format("#define YGE_VERSION \"%s.%s.%s\"\n", yakrebMajorVersion, yakrebMinorVersion, date)

    local versionHeaderPath = path.join("Yakreb/src/Yakreb/Core", "Version.h")

    local versionHeader = io.open(versionHeaderPath, "w")

    versionHeader:write(content)
    versionHeader:close()
end

generate_version()