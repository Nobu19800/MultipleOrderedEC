None = -1
CREATED = 0
INACTIVE = 1
ACTIVE = 2
ERROR  = 3



function load_comp(path,name)
	if path ~= "" then
		package.path =  path..package.path
	end
	require(name)
	m_test = MainLules_object




	for i = 1,table.maxn(CompList) do
		m_test:addMainRule()
		local m =  m_test:getMainRule(i-1)
		for j = 1,table.maxn(CompList[i][1]) do
			m:addaddRule(CompList[i][1][j][1], CompList[i][1][j][2])
		end

		for j = 1,table.maxn(CompList[i][2]) do
			m:addRule()
			local R = m:getRule(j-1)
			for k = 1,table.maxn(CompList[i][2][j]) do
				R:addP()
				for l = 1,table.maxn(CompList[i][2][j][k]) do
					R:addsubRule(k-1, CompList[i][2][j][k][l])
				end
			end
		end
	end


end
