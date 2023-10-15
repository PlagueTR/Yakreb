include "Version.lua"

function generate_version()
    print("Generating version header for project...")

    local scriptDir = path.getdirectory(_SCRIPT)
    local projectRoot = path.join(scriptDir, "../..")

    os.chdir(projectRoot)

    local currentCommit = string.gsub(io.popen("git rev-parse HEAD", "r"):read("*a"), "%s+", "")

    local commitDate = string.gsub(io.popen("git show -s --format=format:%cs " .. currentCommit, "r"):read("*a"), "%s+", "")

    local commitYear, commitMonth, commitDay = commitDate:match("(%d+)-(%d+)-(%d+)")
    local commitTS1 = os.time({year=tonumber(commitYear), month=tonumber(commitMonth), day=tonumber(commitDay)}) + (24 * 60 * 60)
    local commitDate1 = os.date("%Y-%m-%d", commitTS1)

    local commitsOnDate = io.popen("git log --reverse --after=\"" .. commitDate .. " 00:00\" --before=\"" .. commitDate1 .. " 00:00\" --format=%H"):read("*a")

    local commitPosition = 1
    for commit in commitsOnDate:gmatch"([^\r?\n]+)\r?\n" do
        if commit == currentCommit then
            break
        end
        commitPosition = commitPosition + 1
    end

    local yakrebVersionMicro = commitDate .. "-b" .. tostring(commitPosition)

    local content = string.format("#define YGE_VERSION \"%s.%s.%s\"\n", yakrebVersionMajor, yakrebVersionMinor, yakrebVersionMicro)

    local versionHeaderPath = path.join("Yakreb/src/Yakreb/Core", "Version.h")

    local versionHeader = io.open(versionHeaderPath, "w")

    versionHeader:write(content)
    versionHeader:close()
end

generate_version()